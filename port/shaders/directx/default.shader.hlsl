@prism(type='hlsl', name='Fast3D HLSL Shader', version='1.0.0', description='Ported shader to prism', author='Emill & Prism Team')

@if(o_root_signature)
    @if(o_textures[0])
        #define RS "RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | DENY_VERTEX_SHADER_ROOT_ACCESS), CBV(b0, visibility = SHADER_VISIBILITY_PIXEL), DescriptorTable(SRV(t0), visibility = SHADER_VISIBILITY_PIXEL), DescriptorTable(Sampler(s0), visibility = SHADER_VISIBILITY_PIXEL)"
    @end
    @if(o_textures[1])
        #define RS "RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | DENY_VERTEX_SHADER_ROOT_ACCESS), CBV(b0, visibility = SHADER_VISIBILITY_PIXEL), DescriptorTable(SRV(t1), visibility = SHADER_VISIBILITY_PIXEL), DescriptorTable(Sampler(s1), visibility = SHADER_VISIBILITY_PIXEL)"
    @end
@end

struct PSInput {
    float4 position : SV_POSITION;
    @{update_floats(1)} // aMtxSlot vertex attribute (matrix palette index)
@for(i in 0..2)
    @if(o_textures[i])
        float2 uv@{i} : TEXCOORD@{i};
        @{update_floats(2)}
    @end
@end

@if(o_fog)
// Interstage only: computed in the vertex shader, not a vertex attribute
float fogFactor : FOG;
@end

@if(o_shade)
    @if(o_alpha)
        float4 shade : SHADE;
        @{update_floats(4)}
    @else
        float3 shade : SHADE;
        @{update_floats(3)}
    @end
@end
};

@if(o_lighting || o_texgen)
// Mirrors struct LightingUniforms in gfx_rendering_api.h
cbuffer LightCB : register(b3) {
    float4 lights[96]; // 3 float4 per light: color/isPoint, dir/kc, pos/kq
    float4 ambient;
    float4 lookat_x;
    float4 lookat_y;
    float4 texgen_uv[2];
    float4 mv_rows[3];
    float4 mv_cols[3];
    int num_lights;
}
@end

// Mirrors struct TransformUniforms in gfx_rendering_api.h
cbuffer TransformCB : register(b4) {
    float4 mtx_palette[32]; // 4 float4 rows per slot
    float4 y_scale;
}

@if(o_textures[0]) 
    Texture2D g_texture0 : register(t0);
    SamplerState g_sampler0 : register(s0);
@end
@if(o_textures[1]) 
    Texture2D g_texture1 : register(t1);
    SamplerState g_sampler1 : register(s1);
@end

@if(o_masks[0]) Texture2D g_textureMask0 : register(t2);
@if(o_masks[1]) Texture2D g_textureMask1 : register(t3);

@if(o_blend[0]) Texture2D g_textureBlend0 : register(t4);
@if(o_blend[1]) Texture2D g_textureBlend1 : register(t5);

@if(o_palette[0] || o_palette[1])
Texture2D g_texturePal : register(t6);
SamplerState g_samplerPal : register(s6);

// One CI tap: fetch the index (nearest sampler) and look it up in the
// 256-entry palette texture. bank is the CI4 bank entry offset.
float4 paletteTap(in Texture2D tex, in SamplerState tSampler, in float2 uv, in float bank) {
    float idx = tex.Sample(tSampler, uv).r;
    return g_texturePal.Sample(g_samplerPal, float2((idx * 255.0 + bank + 0.5) / 256.0, 0.5));
}

// Filtering happens after the palette lookup, like real hardware:
// params.y selects nearest (0), bilinear (1) or N64 three-point (2).
float4 paletteSampleCI(in Texture2D tex, in SamplerState tSampler, in float2 uv, in float2 texSize, in float4 params) {
    if (params.y > 1.5) {
        float2 offset = frac(uv * texSize - float2(0.5, 0.5));
        offset -= step(1.0, offset.x + offset.y);
        float4 c0 = paletteTap(tex, tSampler, uv - offset / texSize, params.x);
        float4 c1 = paletteTap(tex, tSampler, uv - float2(offset.x - sign(offset.x), offset.y) / texSize, params.x);
        float4 c2 = paletteTap(tex, tSampler, uv - float2(offset.x, offset.y - sign(offset.y)) / texSize, params.x);
        return c0 + abs(offset.x) * (c1 - c0) + abs(offset.y) * (c2 - c0);
    } else if (params.y > 0.5) {
        float2 t = uv * texSize - 0.5;
        float2 f = frac(t);
        float2 base = (floor(t) + 0.5) / texSize;
        float2 px = float2(1.0, 0.0) / texSize;
        float2 py = float2(0.0, 1.0) / texSize;
        float4 c00 = paletteTap(tex, tSampler, base, params.x);
        float4 c10 = paletteTap(tex, tSampler, base + px, params.x);
        float4 c01 = paletteTap(tex, tSampler, base + py, params.x);
        float4 c11 = paletteTap(tex, tSampler, base + px + py, params.x);
        return lerp(lerp(c00, c10, f.x), lerp(c01, c11, f.x), f.y);
    } else {
        return paletteTap(tex, tSampler, uv, params.x);
    }
}
@end

cbuffer PerFrameCB : register(b0) {
    uint noise_frame;
    float noise_scale;
}

float random(in float3 value) {
    float random = dot(value, float3(12.9898, 78.233, 37.719));
    return frac(sin(random) * 143758.5453);
}

// N64 RDP ordered-dither matrices (values 0..7); see applyRdpDither.
static const int kDitherMagic[16] = { 0, 6, 1, 7, 4, 2, 5, 3, 3, 5, 2, 4, 7, 1, 6, 0 };
static const int kDitherBayer[16] = { 0, 4, 1, 5, 6, 2, 7, 3, 1, 5, 0, 4, 7, 3, 6, 2 };

// Integer hash for the G_CD_NOISE dither: robust per-pixel + per-frame value 0..7
// (a sin-based hash aliases to near-constant on some GPUs, washing the noise out).
int ditherNoise(int2 p, int frame) {
    uint h = uint(p.x) * 1597334677u ^ uint(p.y) * 3812015801u ^ uint(frame) * 2654435761u;
    h ^= h >> 16; h *= 2246822519u;
    h ^= h >> 13; h *= 3266489917u;
    h ^= h >> 16;
    return int(h & 7u);
}

// RDP RGB dither + RGBA5551 quantization. mode: 0=magic square, 1=bayer,
// 2=noise (temporal), 3=disable (truncate only), >=4 = off (full precision).
float3 applyRdpDither(float3 color, float modeF, float2 fragCoord, float noiseScale, float frameCount) {
    int mode = int(modeF + 0.5);
    if (mode >= 4) {
        return color;
    }
    float2 nativeCoord = floor(fragCoord * noiseScale);
    float d = 0.0;
    if (mode == 0) {
        int2 cell = int2(nativeCoord) & 3;
        d = float(kDitherMagic[cell.y * 4 + cell.x]);
    } else if (mode == 1) {
        int2 cell = int2(nativeCoord) & 3;
        d = float(kDitherBayer[cell.y * 4 + cell.x]);
    } else if (mode == 2) {
        d = float(ditherNoise(int2(nativeCoord), (int) frameCount));
    }
    float3 q = min(floor(clamp(color * 255.0 + d, 0.0, 255.0) / 8.0), 31.0);
    return (q * 8.0 + floor(q / 4.0)) / 255.0;
}

// Per-draw constants: texture metadata for 3-point filtering plus the combiner
// constant operands (prim, env, keys, K4/K5, fog/grayscale colors).
// Layout must mirror struct PerDrawCB in gfx_direct3d_common.h.
cbuffer PerDrawCB : register(b1) {
    struct {
        uint width;
        uint height;
        bool linear_filtering;
    } textures[7];
    float4 combiner_inputs[6];
    float4 fog_color;
    float4 grayscale_color;
    float4 uv_transform[2];
    float4 texture_clamp[2];
    float4 fog_params;
    float4 palette_params[2];
    float4 lod_params; // x = res scale, y = prim_lod_min, z = G_TD mode
    // Game-bindable register file; lockstep with PerDrawCB in gfx_direct3d_common.h
    float4 uCustom[16];
}

// 3 point texture filtering
// Original author: ArthurCarvalho
// Based on GLSL implementation by twinaphex, mupen64plus-libretro project.

@if(o_three_point_filtering && (o_textures[0] || o_textures[1]))
#define TEX_OFFSET(tex, tSampler, texCoord, off, texSize) tex.Sample(tSampler, texCoord - off / texSize)

float4 tex2D3PointFilter(in Texture2D tex, in SamplerState tSampler, in float2 texCoord, in float2 texSize) {
    float2 offset = frac(texCoord * texSize - float2(0.5, 0.5));
    offset -= step(1.0, offset.x + offset.y);
    float4 c0 = TEX_OFFSET(tex, tSampler, texCoord, offset, texSize);
    float4 c1 = TEX_OFFSET(tex, tSampler, texCoord, float2(offset.x - sign(offset.x), offset.y), texSize);
    float4 c2 = TEX_OFFSET(tex, tSampler, texCoord, float2(offset.x, offset.y - sign(offset.y)), texSize);
    return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);
}
@end

@if(o_prim_depth || o_uses_lod)
cbuffer PerPrimDepthCB : register(b2) {
    float prim_depth;
    float lod_max;
    float2 _pad; // pad to 16-byte cbuffer alignment
}
@end

PSInput VSMain(
    float4 position : POSITION
    , float mtxSlot : MTXSLOT
@for(i in 0..2)
    @if(o_textures[i])
        , float2 uv@{i} : TEXCOORD@{i}
    @end
@end
@if(o_shade || o_lighting)
    @if(o_alpha)
        , float4 shade : SHADE
    @else
        , float3 shade : SHADE
    @end
@end
) {
    PSInput result;

    // RSP position transform: matrix palette entry selected per vertex
    int mtxBase = int(mtxSlot + 0.5) * 4;
    float4 clipPos = position.x * mtx_palette[mtxBase] + position.y * mtx_palette[mtxBase + 1] +
                     position.z * mtx_palette[mtxBase + 2] + position.w * mtx_palette[mtxBase + 3];

    // D3D clip space: z in 0..1; y flip is carried in the uniform
    result.position = float4(clipPos.x, clipPos.y * y_scale.x, (clipPos.z + clipPos.w) / 2.0, clipPos.w);
    @for(i in 0..2)
        @if(o_textures[i])
            // Tile shift/origin/bilerp/size pipeline folded into one transform
            result.uv@{i} = float2(uv@{i}.x * uv_transform[@{i}].x + uv_transform[@{i}].y,
                                   uv@{i}.y * uv_transform[@{i}].z + uv_transform[@{i}].w);
        @end
    @end

    @if(o_fog)
        // N64 RSP fog from clip-space z/w;
        // fog_params.w selects the source (0: computed, 1: constant, 2: vertex alpha)
        float fogZ = clipPos.z;
        float fogW = abs(clipPos.w) < 0.001 ? 0.001 : clipPos.w;
        float fogWinv = 1.0 / fogW;
        if (fogWinv < 0.0) {
            fogWinv = 32767.0;
        }
        float fogCalc = clamp(fogZ * fogWinv * fog_params.x + fog_params.y, 0.0, 255.0) / 255.0;
        @if(o_shade && o_alpha)
            result.fogFactor = fog_params.w > 1.5 ? shade.a : (fog_params.w > 0.5 ? fog_params.z : fogCalc);
        @else
            result.fogFactor = fog_params.w > 0.5 ? fog_params.z : fogCalc;
        @end
    @end

    @if(o_shade && o_alpha)
        // Standard fog forces shade alpha to 1.0; blend-color mode preserves it
        float shadeAlpha = shade.a;
        @if(o_fog)
            if (fog_params.w < 0.5 || fog_params.w > 1.5) {
                shadeAlpha = 1.0;
            }
        @end
    @end

    @if(o_texgen)
        // N64 texgen: project the vertex normal onto the lookat vectors, then run
        // the result through the tile/scale UV pipeline (folded into texgen_uv).
        float texgenDotX = clamp(dot(shade.xyz, lookat_x.xyz) / 127.0, -1.0, 1.0);
        float texgenDotY = clamp(dot(shade.xyz, lookat_y.xyz) / 127.0, -1.0, 1.0);
        @if(o_texgen_linear)
            texgenDotX = acos(-texgenDotX) * 0.159155;
            texgenDotY = acos(-texgenDotY) * 0.159155;
        @else
            texgenDotX = (texgenDotX + 1.0) / 4.0;
            texgenDotY = (texgenDotY + 1.0) / 4.0;
        @end
        @if(o_textures[0])
            result.uv0 = float2(texgenDotX * texgen_uv[0].x + texgen_uv[0].y,
                                texgenDotY * texgen_uv[0].z + texgen_uv[0].w);
        @end
        @if(o_textures[1])
            result.uv1 = float2(texgenDotX * texgen_uv[1].x + texgen_uv[1].y,
                                texgenDotY * texgen_uv[1].z + texgen_uv[1].w);
        @end
    @end

    @if(o_point_lighting)
        // World-space position derived from the object-space vertex position
        float3 worldPos = float3(dot(position, mv_cols[0]), dot(position, mv_cols[1]), dot(position, mv_cols[2]));
    @end
    @if(o_shade)
        @if(o_lighting)
            // N64 RSP lighting: the shade input carries the raw signed vertex normal
            float3 litColor = ambient.rgb;
            for (int i = 0; i < num_lights; i++) {
                float intensity = 0.0;
                @if(o_point_lighting)
                if (lights[i * 3].w > 0.5) {
                    float3 distVec = lights[i * 3 + 2].xyz - worldPos;
                    float distSq = distVec.x * distVec.x + distVec.y * distVec.y + distVec.z * distVec.z * 2.0;
                    float dist = sqrt(distSq);
                    float3 lightModel = float3(dot(distVec, mv_rows[0].xyz), dot(distVec, mv_rows[1].xyz),
                                               dot(distVec, mv_rows[2].xyz));
                    float3 lightIntensity = clamp(4.0 * lightModel / distSq, -1.0, 1.0);
                    float totalIntensity = clamp(dot(lightIntensity, shade.xyz), -1.0, 1.0);
                    float distF = floor(dist);
                    float attenuation = (distF * lights[i * 3 + 1].w * 2.0 +
                                         distF * distF * lights[i * 3 + 2].w / 8.0) / 65535.0 + 1.0;
                    intensity = totalIntensity / attenuation;
                } else {
                    intensity = dot(shade.xyz, lights[i * 3 + 1].xyz) / 127.0;
                }
                @else
                    intensity = dot(shade.xyz, lights[i * 3 + 1].xyz) / 127.0;
                @end
                if (intensity > 0.0) {
                    litColor += intensity * lights[i * 3].rgb;
                }
            }
            litColor = min(litColor, float3(1.0, 1.0, 1.0));
            @if(o_alpha)
                result.shade = float4(litColor, shadeAlpha);
            @else
                result.shade = litColor;
            @end
        @else
            @if(o_alpha)
                result.shade = float4(shade.rgb, shadeAlpha);
            @else
                result.shade = shade;
            @end
        @end
    @end

    return result;
}

@if(o_root_signature)
    [RootSignature(RS)]
@end

#define MOD(x, y) ((x) - (y) * floor((x)/(y)))
#define WRAP(x, low, high) MOD((x)-(low), (high)-(low)) + (low)

struct PSOutput {
    float4 color : SV_TARGET;
    @if(o_prim_depth)
    float depth : SV_Depth;
    @end
};

PSOutput PSMain(PSInput input, float4 screenSpace : SV_Position) {
    @if(o_uses_lod)
        float lodFrac = 0.0;
    @end
    @for(i in 0..2)
        @if(o_textures[i])
            float2 tc@{i} = input.uv@{i};
            @{s = o_clamp[i][0]}
            @{t = o_clamp[i][1]}
            @if(s || t)
                int2 texSize@{i};
                g_texture@{i}.GetDimensions(texSize@{i}.x, texSize@{i}.y);
                @if(s && t)
                    tc@{i} = clamp(tc@{i}, 0.5 / texSize@{i}, texture_clamp[@{i}].xy);
                @elseif(s)
                    tc@{i} = float2(clamp(tc@{i}.x, 0.5 / texSize@{i}.x, texture_clamp[@{i}].x), tc@{i}.y);
                @else
                    tc@{i} = float2(tc@{i}.x, clamp(tc@{i}.y, 0.5 / texSize@{i}.y, texture_clamp[@{i}].y));
                @end
            @end

            @if(i == 0)
                @if(o_uses_lod)
                    @if(!s && !t)
                        int2 texSize0;
                        g_texture0.GetDimensions(texSize0.x, texSize0.y);
                    @end
                    // N64 texture LOD (RDP-accurate): max absolute UV derivative,
                    // linear fraction between tiles, sharpen/detail handling
                    float2 lodScaled = tc0 * float2(texSize0);
                    float2 lodMaxD = max(abs(ddx(lodScaled)), abs(ddy(lodScaled)));
                    float lodMaxDst = max(max(lodMaxD.x, lodMaxD.y) * lod_params.x, 0.000001);
                    if (lod_params.z > 0.5) { // sharpen or detail
                        lodMaxDst = max(lodMaxDst, lod_params.y);
                    }
                    float lodTileBase = floor(log2(lodMaxDst));
                    lodFrac = lodMaxDst / exp2(max(lodTileBase, 0.0)) - 1.0;
                    if (lod_params.z > 0.5 && lod_params.z < 1.5 && lodMaxDst < 1.0) { // sharpen
                        lodFrac = lodMaxDst - 1.0;
                    }
                    if (lod_params.z > 1.5) { // detail: tile 0 is the detail texture
                        if (lodFrac < 0.0) {
                            lodFrac = lodMaxDst;
                        }
                        lodTileBase += 1.0;
                    } else if (lodTileBase >= lod_max) {
                        lodFrac = 1.0;
                    }
                    if (lod_params.z > 0.5) {
                        lodTileBase = max(lodTileBase, 0.0);
                    } else {
                        lodFrac = max(lodFrac, 0.0);
                    }
                    float lodTile0 = clamp(lodTileBase, 0.0, lod_max);
                    float lodTile1 = clamp(lodTileBase + 1.0, 0.0, lod_max);
                    // No real LOD level beyond the base (max level 0): the N64 never
                    // blends a second tile. Small EXTRA_TILE_MIPMAPS textures
                    // degenerate to one level yet still emit G_TL_LOD+TRILERP; without
                    // this the combiner blends a stale TEXEL1 by distance.
                    if (lod_max < 0.5) {
                        lodFrac = 0.0;
                    }
                @end
            @end

            @if(i == 0 && o_mip_lod)
                float4 texVal0 = g_texture0.SampleLevel(g_sampler0, tc0, lodTile0);
                @if(o_masks[0])
                    @if(o_blend[0])
                        float4 blendVal0 = g_textureBlend0.Sample(g_sampler0, tc0);
                    @else
                        float4 blendVal0 = float4(0, 0, 0, 0);
                    @end
                    texVal0 = lerp(texVal0, blendVal0, g_textureMask0.Sample(g_sampler0, tc0).a);
                @end
            @elseif(o_palette[i])
                @if(!s && !t)
                    @if(i == 1)
                        int2 texSize1;
                        g_texture1.GetDimensions(texSize1.x, texSize1.y);
                    @elseif(!o_uses_lod)
                        int2 texSize0;
                        g_texture0.GetDimensions(texSize0.x, texSize0.y);
                    @end
                @end
                float4 texVal@{i} = paletteSampleCI(g_texture@{i}, g_sampler@{i}, tc@{i}, float2(texSize@{i}), palette_params[@{i}]);
            @elseif(o_three_point_filtering)
                float4 texVal@{i};
                if (textures[@{i}].linear_filtering) {
                    @if(o_masks[i])
                        texVal@{i} = tex2D3PointFilter(g_texture@{i}, g_sampler@{i}, tc@{i}, float2(textures[@{i}].width, textures[@{i}].height));
                        float2 maskSize@{i};
                        g_textureMask@{i}.GetDimensions(maskSize@{i}.x, maskSize@{i}.y);
                        float4 maskVal@{i} = tex2D3PointFilter(g_textureMask@{i}, g_sampler@{i}, tc@{i}, maskSize@{i});
                        @if(o_blend[i])
                            float4 blendVal@{i} = tex2D3PointFilter(g_textureBlend@{i}, g_sampler@{i}, tc@{i}, float2(textures[@{i}].width, textures[@{i}].height));
                        @else
                            float4 blendVal@{i} = float4(0, 0, 0, 0);
                        @end

                        texVal@{i} = lerp(texVal@{i}, blendVal@{i}, maskVal@{i}.a);
                    @else
                        texVal@{i} = tex2D3PointFilter(g_texture@{i}, g_sampler@{i}, tc@{i}, float2(textures[@{i}].width, textures[@{i}].height));
                    @end
                } else {
                    texVal@{i} = g_texture@{i}.Sample(g_sampler@{i}, tc@{i});
                    @if(o_masks[i])
                        @if(o_blend[i])
                            float4 blendVal@{i} = g_textureBlend@{i}.Sample(g_sampler@{i}, tc@{i});
                        @else
                            float4 blendVal@{i} = float4(0, 0, 0, 0);
                        @end
                        texVal@{i} = lerp(texVal@{i}, blendVal@{i}, g_textureMask@{i}.Sample(g_sampler@{i}, tc@{i}).a);
                    @end
                }
            @else
                float4 texVal@{i} = g_texture@{i}.Sample(g_sampler@{i}, tc@{i});
                @if(o_masks[i])
                    @if(o_blend[i])
                        float4 blendVal@{i} = g_textureBlend@{i}.Sample(g_sampler@{i}, tc@{i});
                    @else
                        float4 blendVal@{i} = float4(0, 0, 0, 0);
                    @end
                    texVal@{i} = lerp(texVal@{i}, blendVal@{i}, g_textureMask@{i}.Sample(g_sampler@{i}, tc@{i}).a);
                @end
            @end
        @end
    @end

    @if(o_mip_lod)
        // TEXEL1 reads the next mip level of texture 0
        float4 texVal1 = g_texture0.SampleLevel(g_sampler0, tc0, lodTile1);
    @end

    @if(o_two_tile_lod)
        // N64 LOD tile selection: TEXEL0's tile clamps to the max level; the
        // hardware's second texel is always lod_tile + 1 (real tile 1).
        texVal0 = lodTile0 < 0.5 ? texVal0 : texVal1;
    @end

    @if(o_alpha)
        float4 texel;
    @else
        float3 texel;
    @end

    @if(o_2cyc)
        @{f_range = 2}
    @else
        @{f_range = 1}
    @end

    @for(c in 0..f_range)
        @if(c == 1)
            @if(o_alpha)
                @if(o_c[c][1][2] == SHADER_COMBINED)
                    texel.a = WRAP(texel.a, -1.01, 1.01);
                @else
                    texel.a = WRAP(texel.a, -0.51, 1.51);
                @end
            @end

            @if(o_c[c][0][2] == SHADER_COMBINED)
                texel.rgb = WRAP(texel.rgb, -1.01, 1.01);
            @else
                texel.rgb = WRAP(texel.rgb, -0.51, 1.51);
            @end
        @end

        @if(!o_color_alpha_same[c] && o_alpha)
            texel = float4(@{
            append_formula(o_c[c], o_do_single[c][0],
                           o_do_multiply[c][0], o_do_mix[c][0], false, false, true, c == 0)
            }, @{append_formula(o_c[c], o_do_single[c][1],
                           o_do_multiply[c][1], o_do_mix[c][1], true, true, true, c == 0)
            });
        @else
            texel = @{append_formula(o_c[c], o_do_single[c][0],
                           o_do_multiply[c][0], o_do_mix[c][0], o_alpha, false,
                           o_alpha, c == 0)};
        @end
    @end

    @if(o_texture_edge && o_alpha)
        if (texel.a > 0.19) texel.a = 1.0; else discard;
    @end

    texel = WRAP(texel, -0.51, 1.51);
    texel = clamp(texel, 0.0, 1.0);
    // TODO discard if alpha is 0?
    @if(o_fog)
        @if(o_alpha)
            texel = float4(lerp(texel.rgb, fog_color.rgb, input.fogFactor), texel.a);
        @else
            texel = lerp(texel, fog_color.rgb, input.fogFactor);
        @end
    @end

    @if(o_grayscale)
        float intensity = (texel.r + texel.g + texel.b) / 3.0;
        float3 new_texel = grayscale_color.rgb * intensity;
        texel.rgb = lerp(texel.rgb, new_texel, grayscale_color.a);
    @end

    @if(o_alpha && o_noise)
        float2 coords = screenSpace.xy * noise_scale;
        texel.a *= round(saturate(random(float3(floor(coords), noise_frame)) + texel.a - 0.5));
    @end

    // N64 RGB framebuffer dither (per-primitive G_CD_* mode in lod_params.w)
    @if(o_alpha)
        texel.rgb = applyRdpDither(texel.rgb, lod_params.w, screenSpace.xy, noise_scale, noise_frame);
    @else
        texel = applyRdpDither(texel, lod_params.w, screenSpace.xy, noise_scale, noise_frame);
    @end

    @if(o_alpha)
        @if(o_alpha_threshold)
            if (texel.a < 8.0 / 256.0) discard;
        @end
        @if(o_invisible)
            texel.a = 0.0;
        @end
    @end

    PSOutput output;
    @if(o_alpha)
        output.color = texel;
    @else
        output.color = float4(texel, 1.0);
    @end
    @if(o_prim_depth)
        output.depth = prim_depth;
    @end
    return output;
}
