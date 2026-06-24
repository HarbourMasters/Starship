@prism(type='metal', name='Fast3D Metal Shader', version='1.0.0', description='Ported shader to prism', author='Emill & Prism Team')

#include <metal_stdlib>
using namespace metal;

// BEGIN VERTEX SHADER
struct FrameUniforms {
    int frameCount;
    float noiseScale;
};

struct DrawUniforms {
    int textureFiltering[7];
    float prim_depth;
    float lod_max;
    float4 inputs[6];
    float4 fog_color;
    float4 grayscale_color;
    float4 uv_transform[2];
    float4 texture_clamp[2];
    float4 fog_params;
    float4 palette_params[2];
    float4 lod_params;
    // Game-bindable register file; lockstep with DrawUniforms in gfx_metal.h
    float4 uCustom[32];
    float4 debug_tint;
};

@if(o_lighting || o_texgen)
// Mirrors struct LightingUniforms in gfx_rendering_api.h
struct LightUniforms {
    float4 lights[96]; // 3 float4 per light: color/isPoint, dir/kc, pos/kq
    float4 ambient;
    float4 lookat_x;
    float4 lookat_y;
    float4 texgen_uv[2];
    float4 mv_rows[3];
    float4 mv_cols[3];
    int num_lights;
};
@end

// Mirrors struct TransformUniforms in gfx_rendering_api.h
struct TransformUniforms {
    float4 mtx_palette[32]; // 4 float4 rows per slot
    float4 y_scale;
};

struct FragOut {
    float4 color [[color(0)]];
    @if(o_prim_depth)
    float depth [[depth(any)]];
    @end
};

struct Vertex {
    float4 position [[attribute(@{get_vertex_index()})]];
    @{update_floats(4)}
    float mtxSlot [[attribute(@{get_vertex_index()})]];
    @{update_floats(1)}
    @for(i in 0..2)
        @if(o_textures[i])
            float2 texCoord@{i} [[attribute(@{get_vertex_index()})]];
            @{update_floats(2)}
        @end
    @end
    @if(o_shade || o_lighting)
        @if(o_alpha)
            float4 shade [[attribute(@{get_vertex_index()})]];
            @{update_floats(4)}
        @else
            float3 shade [[attribute(@{get_vertex_index()})]];
            @{update_floats(3)}
        @end
    @end
};

struct ProjectedVertex {
    @for(i in 0..2)
        @if(o_textures[i])
            float2 texCoord@{i};
        @end
    @end
    @if(o_fog)
        float fogFactor;
    @end
    @if(o_shade)
        @if(o_alpha)
            float4 shade;
        @else
            float3 shade;
        @end
    @end
    float4 position [[position]];
};

vertex ProjectedVertex vertexShader(Vertex in [[stage_in]]
    , constant DrawUniforms& drawUniforms [[buffer(2)]]
    , constant TransformUniforms& transformUniforms [[buffer(3)]]
@if(o_lighting || o_texgen)
    , constant LightUniforms& lightUniforms [[buffer(1)]]
@end
) {
    ProjectedVertex out;

    // RSP position transform: matrix palette entry selected per vertex
    int mtxBase = int(in.mtxSlot + 0.5) * 4;
    float4 clipPos = in.position.x * transformUniforms.mtx_palette[mtxBase] +
                     in.position.y * transformUniforms.mtx_palette[mtxBase + 1] +
                     in.position.z * transformUniforms.mtx_palette[mtxBase + 2] +
                     in.position.w * transformUniforms.mtx_palette[mtxBase + 3];

    @for(i in 0..2)
        @if(o_textures[i])
            // Tile shift/origin/bilerp/size pipeline folded into one transform
            out.texCoord@{i} = float2(in.texCoord@{i}.x * drawUniforms.uv_transform[@{i}].x + drawUniforms.uv_transform[@{i}].y,
                                      in.texCoord@{i}.y * drawUniforms.uv_transform[@{i}].z + drawUniforms.uv_transform[@{i}].w);
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
        float fogCalc = clamp(fogZ * fogWinv * drawUniforms.fog_params.x + drawUniforms.fog_params.y, 0.0, 255.0) / 255.0;
        @if(o_shade && o_alpha)
            out.fogFactor = drawUniforms.fog_params.w > 1.5 ? in.shade.w
                            : (drawUniforms.fog_params.w > 0.5 ? drawUniforms.fog_params.z : fogCalc);
        @else
            out.fogFactor = drawUniforms.fog_params.w > 0.5 ? drawUniforms.fog_params.z : fogCalc;
        @end
    @end
    @if(o_texgen)
        // N64 texgen: project the vertex normal onto the lookat vectors, then
        // run the result through the tile/scale UV pipeline (folded into the
        // per-draw texgen linear transforms).
        float texgenDotX = clamp(dot(in.shade.xyz, lightUniforms.lookat_x.xyz) / 127.0, -1.0, 1.0);
        float texgenDotY = clamp(dot(in.shade.xyz, lightUniforms.lookat_y.xyz) / 127.0, -1.0, 1.0);
        @if(o_texgen_linear)
            texgenDotX = acos(-texgenDotX) * 0.159155;
            texgenDotY = acos(-texgenDotY) * 0.159155;
        @else
            texgenDotX = (texgenDotX + 1.0) / 4.0;
            texgenDotY = (texgenDotY + 1.0) / 4.0;
        @end
        @if(o_textures[0])
            out.texCoord0 = float2(texgenDotX * lightUniforms.texgen_uv[0].x + lightUniforms.texgen_uv[0].y,
                                   texgenDotY * lightUniforms.texgen_uv[0].z + lightUniforms.texgen_uv[0].w);
        @end
        @if(o_textures[1])
            out.texCoord1 = float2(texgenDotX * lightUniforms.texgen_uv[1].x + lightUniforms.texgen_uv[1].y,
                                   texgenDotY * lightUniforms.texgen_uv[1].z + lightUniforms.texgen_uv[1].w);
        @end
    @end
    @if(o_shade && o_alpha)
        // Standard fog forces shade alpha to 1.0; blend-color mode preserves it
        float shadeAlpha = in.shade.w;
        @if(o_fog)
            if (drawUniforms.fog_params.w < 0.5 || drawUniforms.fog_params.w > 1.5) {
                shadeAlpha = 1.0;
            }
        @end
    @end
    @if(o_point_lighting)
        // World-space position derived from the object-space vertex position
        float3 worldPos = float3(dot(in.position, lightUniforms.mv_cols[0]),
                                 dot(in.position, lightUniforms.mv_cols[1]),
                                 dot(in.position, lightUniforms.mv_cols[2]));
    @end
    @if(o_shade)
        @if(o_lighting)
            // N64 RSP lighting: in.shade carries the raw signed vertex normal
            float3 litColor = lightUniforms.ambient.xyz;
            for (int i = 0; i < lightUniforms.num_lights; i++) {
                float intensity = 0.0;
                @if(o_point_lighting)
                if (lightUniforms.lights[i * 3].w > 0.5) {
                    float3 distVec = lightUniforms.lights[i * 3 + 2].xyz - worldPos;
                    float distSq = distVec.x * distVec.x + distVec.y * distVec.y + distVec.z * distVec.z * 2.0;
                    float dist = sqrt(distSq);
                    float3 lightModel = float3(dot(distVec, lightUniforms.mv_rows[0].xyz),
                                               dot(distVec, lightUniforms.mv_rows[1].xyz),
                                               dot(distVec, lightUniforms.mv_rows[2].xyz));
                    float3 lightIntensity = clamp(4.0 * lightModel / distSq, -1.0, 1.0);
                    float totalIntensity = clamp(dot(lightIntensity, in.shade.xyz), -1.0, 1.0);
                    float distF = floor(dist);
                    float attenuation = (distF * lightUniforms.lights[i * 3 + 1].w * 2.0 +
                                         distF * distF * lightUniforms.lights[i * 3 + 2].w / 8.0) / 65535.0 + 1.0;
                    intensity = totalIntensity / attenuation;
                } else {
                    intensity = dot(in.shade.xyz, lightUniforms.lights[i * 3 + 1].xyz) / 127.0;
                }
                @else
                    intensity = dot(in.shade.xyz, lightUniforms.lights[i * 3 + 1].xyz) / 127.0;
                @end
                if (intensity > 0.0) {
                    litColor += intensity * lightUniforms.lights[i * 3].xyz;
                }
            }
            litColor = min(litColor, float3(1.0));
            @if(o_alpha)
                out.shade = float4(litColor, shadeAlpha);
            @else
                out.shade = litColor;
            @end
        @else
            @if(o_alpha)
                out.shade = float4(in.shade.xyz, shadeAlpha);
            @else
                out.shade = in.shade;
            @end
        @end
    @end
    // Metal clip space: z in 0..1; y flip is carried in the uniform
    out.position = float4(clipPos.x, clipPos.y * transformUniforms.y_scale.x,
                          (clipPos.z + clipPos.w) / 2.0, clipPos.w);
    return out;
}
// END - BEGIN FRAGMENT SHADER

float mod(float x, float y) {
    return float(x - y * floor(x / y));
}

float3 mod(float3 a, float3 b) {
    return float3(a.x - b.x * floor(a.x / b.x), a.y - b.y * floor(a.y / b.y), a.z - b.z * floor(a.z / b.z));
}

float4 mod(float4 a, float4 b) {
    return float4(a.x - b.x * floor(a.x / b.x), a.y - b.y * floor(a.y / b.y), a.z - b.z * floor(a.z / b.z), a.w - b.w * floor(a.w / b.w));
}

#define WRAP(x, low, high) mod((x)-(low), (high)-(low)) + (low)
#define TEX_OFFSET(tex, texSmplr, texCoord, off, texSize) tex.sample(texSmplr, texCoord - off / texSize)

float4 filter3point(thread const texture2d<float> tex, thread const sampler texSmplr, thread const float2& texCoord, thread const float2& texSize) {
    float2 offset = fract((texCoord * texSize) - float2(0.5));
    offset -= float2(step(1.0, offset.x + offset.y));
    float4 c0 = TEX_OFFSET(tex, texSmplr, texCoord, offset, texSize);
    float4 c1 = TEX_OFFSET(tex, texSmplr, texCoord, float2(offset.x - sign(offset.x), offset.y), texSize);
    float4 c2 = TEX_OFFSET(tex, texSmplr, texCoord, float2(offset.x, offset.y - sign(offset.y)), texSize);
    return c0 + abs(offset.x) * (c1 - c0) + abs(offset.y) * (c2 - c0);
}

float4 hookTexture2D(thread const texture2d<float> tex, thread const sampler texSmplr, thread const float2& uv, thread const float2& texSize, thread const int filtering) {
@if(o_three_point_filtering)
    if(filtering == @{FILTER_THREE_POINT}) {
        return filter3point(tex, texSmplr, uv, texSize);
    }
@end
    return tex.sample(texSmplr, uv);
}

float random(float3 value) {
    float random = dot(sin(value), float3(12.9898, 78.233, 37.719));
    return fract(sin(random) * 143758.5453);
}

// N64 RDP ordered-dither matrices (values 0..7) added to the 8-bit color before
// truncation to 5 bits, recreating the RGBA5551 framebuffer grain.
constant int kDitherMagic[16] = { 0, 6, 1, 7, 4, 2, 5, 3, 3, 5, 2, 4, 7, 1, 6, 0 };
constant int kDitherBayer[16] = { 0, 4, 1, 5, 6, 2, 7, 3, 1, 5, 0, 4, 7, 3, 6, 2 };

// Integer hash for the G_CD_NOISE dither: a robust per-pixel + per-frame value 0..7.
// (The sin-based random() above aliases to near-constant on some GPUs, which washed
// the noise out so it was invisible while the ordered matrices worked fine.)
int ditherNoise(int2 p, int frame) {
    uint h = uint(p.x) * 1597334677u ^ uint(p.y) * 3812015801u ^ uint(frame) * 2654435761u;
    h ^= h >> 16; h *= 2246822519u;
    h ^= h >> 13; h *= 3266489917u;
    h ^= h >> 16;
    return int(h & 7u);
}

// Applies the RDP's RGB dither + 5-bit quantization, matching the per-primitive
// G_CD_* mode. mode: 0=magic square, 1=bayer, 2=noise (temporal), 3=disable
// (truncate only), >=4 = feature off (full precision passthrough). Dither cells are
// scaled to native resolution via noiseScale so the grain looks hardware-accurate.
float3 applyRdpDither(float3 color, float modeF, float2 fragCoord, float noiseScale, int frameCount) {
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
        d = float(ditherNoise(int2(nativeCoord), frameCount));
    }
    float3 q = min(floor(clamp(color * 255.0 + d, 0.0, 255.0) / 8.0), 31.0);
    return (q * 8.0 + floor(q / 4.0)) / 255.0;
}

@if(o_palette[0] || o_palette[1])
// One CI tap: fetch the index (nearest sampler) and look it up in the
// 256-entry palette texture. bank is the CI4 bank entry offset.
float4 paletteTap(thread const texture2d<float> tex, thread const sampler texSmplr,
                  thread const texture2d<float> pal, thread const sampler palSmplr,
                  float2 uv, float bank) {
    float idx = tex.sample(texSmplr, uv).r;
    return pal.sample(palSmplr, float2((idx * 255.0 + bank + 0.5) / 256.0, 0.5));
}

// Filtering happens after the palette lookup, like real hardware:
// params.y selects nearest (0), bilinear (1) or N64 three-point (2).
float4 paletteSample(thread const texture2d<float> tex, thread const sampler texSmplr,
                     thread const texture2d<float> pal, thread const sampler palSmplr,
                     float2 uv, float2 texSize, float4 params) {
    if (params.y > 1.5) {
        float2 offset = fract(uv * texSize - float2(0.5));
        offset -= float2(step(1.0, offset.x + offset.y));
        float4 c0 = paletteTap(tex, texSmplr, pal, palSmplr, uv - offset / texSize, params.x);
        float4 c1 = paletteTap(tex, texSmplr, pal, palSmplr, uv - float2(offset.x - sign(offset.x), offset.y) / texSize, params.x);
        float4 c2 = paletteTap(tex, texSmplr, pal, palSmplr, uv - float2(offset.x, offset.y - sign(offset.y)) / texSize, params.x);
        return c0 + abs(offset.x) * (c1 - c0) + abs(offset.y) * (c2 - c0);
    } else if (params.y > 0.5) {
        float2 t = uv * texSize - 0.5;
        float2 f = fract(t);
        float2 base = (floor(t) + 0.5) / texSize;
        float2 px = float2(1.0, 0.0) / texSize;
        float2 py = float2(0.0, 1.0) / texSize;
        float4 c00 = paletteTap(tex, texSmplr, pal, palSmplr, base, params.x);
        float4 c10 = paletteTap(tex, texSmplr, pal, palSmplr, base + px, params.x);
        float4 c01 = paletteTap(tex, texSmplr, pal, palSmplr, base + py, params.x);
        float4 c11 = paletteTap(tex, texSmplr, pal, palSmplr, base + px + py, params.x);
        return mix(mix(c00, c10, f.x), mix(c01, c11, f.x), f.y);
    } else {
        return paletteTap(tex, texSmplr, pal, palSmplr, uv, params.x);
    }
}
@end

fragment FragOut fragmentShader(
    ProjectedVertex in [[stage_in]],
    constant FrameUniforms &frameUniforms [[buffer(0)]],
    constant DrawUniforms &drawUniforms [[buffer(1)]]
@if(o_textures[0])
    , texture2d<float> uTex0 [[texture(0)]], sampler uTex0Smplr [[sampler(0)]]
@end
@if(o_textures[1])
    , texture2d<float> uTex1 [[texture(1)]], sampler uTex1Smplr [[sampler(1)]]
@end
@if(o_masks[0])
    , texture2d<float> uTexMask0 [[texture(2)]]
@end
@if(o_masks[1])
    , texture2d<float> uTexMask1 [[texture(3)]]
@end
@if(o_blend[0])
    , texture2d<float> uTexBlend0 [[texture(4)]]
@end
@if(o_blend[1])
    , texture2d<float> uTexBlend1 [[texture(5)]]
@end
@if(o_palette[0] || o_palette[1])
    , texture2d<float> uTexPal [[texture(6)]], sampler uTexPalSmplr [[sampler(6)]]
@end
) {
    @if(o_uses_lod)
        float lodFrac = 0.0;
    @end
    @for(i in 0..2)
        @if(o_textures[i])
            @{s = o_clamp[i][0]}
            @{t = o_clamp[i][1]}
            float2 texSize@{i} = float2(uTex@{i}.get_width(), uTex@{i}.get_height());
            @if(!s && !t)
                float2 vTexCoordAdj@{i} = in.texCoord@{i};
            @else
                @if(s && t)
                    float2 vTexCoordAdj@{i} = fast::clamp(in.texCoord@{i}, float2(0.5) / texSize@{i}, drawUniforms.texture_clamp[@{i}].xy);
                @elseif(s)
                    float2 vTexCoordAdj@{i} = float2(fast::clamp(in.texCoord@{i}.x, 0.5 / texSize@{i}.x, drawUniforms.texture_clamp[@{i}].x), in.texCoord@{i}.y);
                @else
                    float2 vTexCoordAdj@{i} = float2(in.texCoord@{i}.x, fast::clamp(in.texCoord@{i}.y, 0.5 / texSize@{i}.y, drawUniforms.texture_clamp[@{i}].y));
                @end
            @end

            @if(i == 0)
                @if(o_uses_lod)
                    // N64 texture LOD (RDP-accurate): max absolute UV derivative,
                    // linear fraction between tiles, sharpen/detail handling
                    float2 lodScaled = vTexCoordAdj0 * texSize0;
                    float2 lodMaxD = max(abs(dfdx(lodScaled)), abs(dfdy(lodScaled)));
                    float lodMaxDst = max(max(lodMaxD.x, lodMaxD.y) * drawUniforms.lod_params.x, 0.000001);
                    if (drawUniforms.lod_params.z > 0.5) { // sharpen or detail
                        lodMaxDst = max(lodMaxDst, drawUniforms.lod_params.y);
                    }
                    float lodTileBase = floor(log2(lodMaxDst));
                    lodFrac = lodMaxDst / exp2(max(lodTileBase, 0.0)) - 1.0;
                    if (drawUniforms.lod_params.z > 0.5 && drawUniforms.lod_params.z < 1.5 && lodMaxDst < 1.0) { // sharpen
                        lodFrac = lodMaxDst - 1.0;
                    }
                    if (drawUniforms.lod_params.z > 1.5) { // detail: tile 0 is the detail texture
                        if (lodFrac < 0.0) {
                            lodFrac = lodMaxDst;
                        }
                        lodTileBase += 1.0;
                    } else if (lodTileBase >= drawUniforms.lod_max) {
                        lodFrac = 1.0;
                    }
                    if (drawUniforms.lod_params.z > 0.5) {
                        lodTileBase = max(lodTileBase, 0.0);
                    } else {
                        lodFrac = max(lodFrac, 0.0);
                    }
                    float lodTile0 = clamp(lodTileBase, 0.0, drawUniforms.lod_max);
                    float lodTile1 = clamp(lodTileBase + 1.0, 0.0, drawUniforms.lod_max);
                    // No real LOD level beyond the base (max level 0): the N64 never
                    // blends a second tile. Small EXTRA_TILE_MIPMAPS textures
                    // degenerate to one level yet still emit G_TL_LOD+TRILERP; without
                    // this the combiner blends a stale TEXEL1 by distance.
                    if (drawUniforms.lod_max < 0.5) {
                        lodFrac = 0.0;
                    }
                @end
            @end

            @if(i == 0)
                @if(o_mip_lod)
                    float4 texVal0 = uTex0.sample(uTex0Smplr, vTexCoordAdj0, level(lodTile0));
                @elseif(o_palette[0])
                    float4 texVal0 = paletteSample(uTex0, uTex0Smplr, uTexPal, uTexPalSmplr, vTexCoordAdj0, texSize0, drawUniforms.palette_params[0]);
                @else
                    float4 texVal@{i} = hookTexture2D(uTex@{i}, uTex@{i}Smplr, vTexCoordAdj@{i}, texSize@{i}, drawUniforms.textureFiltering[@{i}]);
                @end
            @else
                @if(o_palette[1])
                    float4 texVal1 = paletteSample(uTex1, uTex1Smplr, uTexPal, uTexPalSmplr, vTexCoordAdj1, texSize1, drawUniforms.palette_params[1]);
                @else
                    float4 texVal@{i} = hookTexture2D(uTex@{i}, uTex@{i}Smplr, vTexCoordAdj@{i}, texSize@{i}, drawUniforms.textureFiltering[@{i}]);
                @end
            @end

            @if(o_masks[i])
                float2 maskSize@{i} = float2(uTexMask@{i}.get_width(), uTexMask@{i}.get_height());
                float4 maskVal@{i} = hookTexture2D(uTexMask@{i}, uTex@{i}Smplr, vTexCoordAdj@{i}, maskSize@{i}, drawUniforms.textureFiltering[@{i}]);
                @if(o_blend[i])
                    float4 blendVal@{i} = hookTexture2D(uTexBlend@{i}, uTex@{i}Smplr, vTexCoordAdj@{i}, texSize@{i}, drawUniforms.textureFiltering[@{i}]);
                @else
                    float4 blendVal@{i} = float4(0, 0, 0, 0);
                @end

                texVal@{i} = mix(texVal@{i}, blendVal@{i}, maskVal@{i}.w);
            @end
        @end
    @end

    @if(o_mip_lod)
        // TEXEL1 reads the next mip level of texture 0
        float4 texVal1 = uTex0.sample(uTex0Smplr, vTexCoordAdj0, level(lodTile1));
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
                    texel.w = WRAP(texel.w, -1.01, 1.01);
                @else
                    texel.w = WRAP(texel.w, -0.51, 1.51);
                @end
            @end

            @if(o_c[c][0][2] == SHADER_COMBINED)
                texel.xyz = WRAP(texel.xyz, -1.01, 1.01);
            @else
                texel.xyz = WRAP(texel.xyz, -0.51, 1.51);
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
        if (texel.w > 0.19) texel.w = 1.0; else discard_fragment();
    @end

    texel = WRAP(texel, -0.51, 1.51);
    texel = clamp(texel, 0.0, 1.0);
    // TODO discard if alpha is 0?

    @if(o_fog)
        @if(o_alpha)
            texel = float4(mix(texel.xyz, drawUniforms.fog_color.xyz, in.fogFactor), texel.w);
        @else
            texel = mix(texel, drawUniforms.fog_color.xyz, in.fogFactor);
        @end
    @end

    @if(o_grayscale)
        float intensity = (texel.x + texel.y + texel.z) / 3.0;
        float3 new_texel = drawUniforms.grayscale_color.xyz * intensity;
        texel.xyz = mix(texel.xyz, new_texel, drawUniforms.grayscale_color.w);
    @end

    @if(o_alpha && o_noise)
        float2 coords = in.position.xy * frameUniforms.noiseScale;
        texel.w *= round(saturate(random(float3(floor(coords), float(frameUniforms.frameCount))) + texel.w - 0.5));
    @end

    // N64 RGB framebuffer dither (per-primitive G_CD_* mode in lod_params.w)
    @if(o_alpha)
        texel.xyz = applyRdpDither(texel.xyz, drawUniforms.lod_params.w, in.position.xy, frameUniforms.noiseScale, frameUniforms.frameCount);
    @else
        texel = applyRdpDither(texel, drawUniforms.lod_params.w, in.position.xy, frameUniforms.noiseScale, frameUniforms.frameCount);
    @end

    // HD-replacement debug tint (no-op when debug_tint.w == 0)
    @if(o_alpha)
        texel.xyz = mix(texel.xyz, drawUniforms.debug_tint.xyz, drawUniforms.debug_tint.w);
    @else
        texel = mix(texel, drawUniforms.debug_tint.xyz, drawUniforms.debug_tint.w);
    @end

    FragOut out;
    @if(o_alpha)
        @if(o_alpha_threshold)
            if (texel.w < 8.0 / 256.0) discard_fragment();
        @end
        @if(o_invisible)
            texel.w = 0.0;
        @end
        out.color = texel;
    @else
        out.color = float4(texel, 1.0);
    @end
    @if(o_prim_depth)
        out.depth = drawUniforms.prim_depth;
    @end
    return out;
}