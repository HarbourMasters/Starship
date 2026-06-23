@prism(type='fragment', name='Fast3D Vulkan Shader', version='1.0.0', description='Fast3D combiner shader for Vulkan', author='Ghostship')

#version 450
@include("shaders/vulkan/include/common.glsli")

@if(VERTEX_SHADER)
    @include("shaders/vulkan/include/fast3d_vs.glsli")

@else
    layout(location = 0) out vec4 vOutColor;

    @for(i in 0..2)
        @if(o_textures[i])
            layout(location = @{i}) in vec2 vTexCoord@{i};
        @end
    @end

    @if(o_fog)
        layout(location = 2) in float vFogFactor;
    @end

    @if(o_shade)
        @if(o_alpha)
            layout(location = 3) in vec4 vShade;
        @else
            layout(location = 3) in vec3 vShade;
        @end
    @end

    @if(o_textures[0]) layout(set = 1, binding = 0) uniform sampler2D uTex0;
    @if(o_textures[1]) layout(set = 1, binding = 1) uniform sampler2D uTex1;

    @if(o_masks[0]) layout(set = 1, binding = 2) uniform sampler2D uTexMask0;
    @if(o_masks[1]) layout(set = 1, binding = 3) uniform sampler2D uTexMask1;

    @if(o_blend[0]) layout(set = 1, binding = 4) uniform sampler2D uTexBlend0;
    @if(o_blend[1]) layout(set = 1, binding = 5) uniform sampler2D uTexBlend1;

    #define TEX_OFFSET(off) texture(tex, texCoord - off / texSize)
    #define WRAP(x, low, high) mod((x)-(low), (high)-(low)) + (low)

    float random(in vec3 value) {
        float random = dot(sin(value), vec3(12.9898, 78.233, 37.719));
        return fract(sin(random) * 143758.5453);
    }

    // N64 RDP ordered-dither matrices (values 0..7); see applyRdpDither.
    const int kDitherMagic[16] = int[16](0, 6, 1, 7, 4, 2, 5, 3, 3, 5, 2, 4, 7, 1, 6, 0);
    const int kDitherBayer[16] = int[16](0, 4, 1, 5, 6, 2, 7, 3, 1, 5, 0, 4, 7, 3, 6, 2);

    // Integer hash for the G_CD_NOISE dither: robust per-pixel + per-frame value 0..7
    // (a sin-based hash aliases to near-constant on some GPUs, washing the noise out).
    int ditherNoise(ivec2 p, int frame) {
        uint h = uint(p.x) * 1597334677u ^ uint(p.y) * 3812015801u ^ uint(frame) * 2654435761u;
        h ^= h >> 16u; h *= 2246822519u;
        h ^= h >> 13u; h *= 3266489917u;
        h ^= h >> 16u;
        return int(h & 7u);
    }

    // RDP RGB dither + RGBA5551 quantization. mode: 0=magic square, 1=bayer,
    // 2=noise (temporal), 3=disable (truncate only), >=4 = off (full precision).
    vec3 applyRdpDither(vec3 color, float modeF, vec2 fragCoord, float noiseScale, int frameCount) {
        int mode = int(modeF + 0.5);
        if (mode >= 4) {
            return color;
        }
        vec2 nativeCoord = floor(fragCoord * noiseScale);
        float d = 0.0;
        if (mode == 0) {
            ivec2 cell = ivec2(nativeCoord) & 3;
            d = float(kDitherMagic[cell.y * 4 + cell.x]);
        } else if (mode == 1) {
            ivec2 cell = ivec2(nativeCoord) & 3;
            d = float(kDitherBayer[cell.y * 4 + cell.x]);
        } else if (mode == 2) {
            d = float(ditherNoise(ivec2(nativeCoord), frameCount));
        }
        vec3 q = min(floor(clamp(color * 255.0 + d, 0.0, 255.0) / 8.0), 31.0);
        return (q * 8.0 + floor(q / 4.0)) / 255.0;
    }

    vec4 filter3point(in sampler2D tex, in vec2 texCoord, in vec2 texSize) {
        vec2 offset = fract(texCoord*texSize - vec2(0.5));
        offset -= step(1.0, offset.x + offset.y);
        vec4 c0 = TEX_OFFSET(offset);
        vec4 c1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));
        vec4 c2 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));
        return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);
    }

    vec4 hookTexture2D(in int id, sampler2D tex, in vec2 uv, in vec2 texSize) {
    @if(o_three_point_filtering)
        if(drawU.tex_filter[0][id] == @{FILTER_THREE_POINT}) {
            return filter3point(tex, uv, texSize);
        }
    @end
        return texture(tex, uv);
    }

    @include("shaders/vulkan/include/palette.glsli")

    void main() {
        @if(o_uses_lod)
            float lodFrac = 0.0;
        @end
        @for(i in 0..2)
            @if(o_textures[i])
                @{s = o_clamp[i][0]}
                @{t = o_clamp[i][1]}

                vec2 texSize@{i} = vec2(textureSize(uTex@{i}, 0));

                @if(!s && !t)
                    vec2 vTexCoordAdj@{i} = vTexCoord@{i};
                @else
                    @if(s && t)
                        vec2 vTexCoordAdj@{i} = clamp(vTexCoord@{i}, 0.5 / texSize@{i}, drawU.tex_clamp[@{i}].xy);
                    @elseif(s)
                        vec2 vTexCoordAdj@{i} = vec2(clamp(vTexCoord@{i}.s, 0.5 / texSize@{i}.s, drawU.tex_clamp[@{i}].x), vTexCoord@{i}.t);
                    @else
                        vec2 vTexCoordAdj@{i} = vec2(vTexCoord@{i}.s, clamp(vTexCoord@{i}.t, 0.5 / texSize@{i}.t, drawU.tex_clamp[@{i}].y));
                    @end
                @end

                @if(i == 0)
                    @if(o_uses_lod)
                        // N64 texture LOD (RDP-accurate): max absolute UV derivative,
                        // linear fraction between tiles, sharpen/detail handling
                        vec2 lodScaled = vTexCoordAdj0 * texSize0;
                        vec2 lodMaxD = max(abs(dFdx(lodScaled)), abs(dFdy(lodScaled)));
                        float lodMaxDst = max(max(lodMaxD.x, lodMaxD.y) * drawU.lod_params.x, 0.000001);
                        if (drawU.lod_params.z > 0.5) { // sharpen or detail
                            lodMaxDst = max(lodMaxDst, drawU.lod_params.y);
                        }
                        float lodTileBase = floor(log2(lodMaxDst));
                        lodFrac = lodMaxDst / exp2(max(lodTileBase, 0.0)) - 1.0;
                        if (drawU.lod_params.z > 0.5 && drawU.lod_params.z < 1.5 && lodMaxDst < 1.0) { // sharpen
                            lodFrac = lodMaxDst - 1.0;
                        }
                        if (drawU.lod_params.z > 1.5) { // detail: tile 0 is the detail texture
                            if (lodFrac < 0.0) {
                                lodFrac = lodMaxDst;
                            }
                            lodTileBase += 1.0;
                        } else if (lodTileBase >= drawU.misc.y) {
                            lodFrac = 1.0;
                        }
                        if (drawU.lod_params.z > 0.5) {
                            lodTileBase = max(lodTileBase, 0.0);
                        } else {
                            lodFrac = max(lodFrac, 0.0);
                        }
                        float lodTile0 = clamp(lodTileBase, 0.0, drawU.misc.y);
                        float lodTile1 = clamp(lodTileBase + 1.0, 0.0, drawU.misc.y);
                        // No real LOD level beyond the base (max level 0): the N64
                        // never blends a second tile. Small EXTRA_TILE_MIPMAPS
                        // textures degenerate to one level yet still emit
                        // G_TL_LOD+TRILERP; without this the combiner blends a stale
                        // TEXEL1 by distance.
                        if (drawU.misc.y < 0.5) {
                            lodFrac = 0.0;
                        }
                    @end
                @end

                @if(i == 0)
                    @if(o_mip_lod)
                        vec4 texVal0 = textureLod(uTex0, vTexCoordAdj0, lodTile0);
                    @elseif(o_palette[0])
                        vec4 texVal0 = paletteSample(uTex0, vTexCoordAdj0, texSize0, drawU.palette_params[0]);
                    @else
                        vec4 texVal@{i} = hookTexture2D(@{i}, uTex@{i}, vTexCoordAdj@{i}, texSize@{i});
                    @end
                @else
                    @if(o_palette[1])
                        vec4 texVal1 = paletteSample(uTex1, vTexCoordAdj1, texSize1, drawU.palette_params[1]);
                    @else
                        vec4 texVal@{i} = hookTexture2D(@{i}, uTex@{i}, vTexCoordAdj@{i}, texSize@{i});
                    @end
                @end

                @if(o_masks[i])
                    vec2 maskSize@{i} = vec2(textureSize(uTexMask@{i}, 0));

                    vec4 maskVal@{i} = hookTexture2D(@{i}, uTexMask@{i}, vTexCoordAdj@{i}, maskSize@{i});

                    @if(o_blend[i])
                        vec4 blendVal@{i} = hookTexture2D(@{i}, uTexBlend@{i}, vTexCoordAdj@{i}, texSize@{i});
                    @else
                        vec4 blendVal@{i} = vec4(0, 0, 0, 0);
                    @end

                    texVal@{i} = mix(texVal@{i}, blendVal@{i}, maskVal@{i}.a);
                @end
            @end
        @end

        @if(o_mip_lod)
            // TEXEL1 reads the next mip level of texture 0
            vec4 texVal1 = textureLod(uTex0, vTexCoordAdj0, lodTile1);
        @end

        @if(o_two_tile_lod)
            // N64 LOD tile selection: TEXEL0's tile is clamped to the max level,
            // but the hardware's second texel is always lod_tile + 1 — at
            // magnification TEXEL1 still reads the real tile 1 (Paper Mario's
            // sprite shading relies on this with a stale G_TL_LOD).
            texVal0 = lodTile0 < 0.5 ? texVal0 : texVal1;
        @end

        @if(o_alpha)
            vec4 texel;
        @else
            vec3 texel;
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
                texel = vec4(@{
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

        texel = WRAP(texel, -0.51, 1.51);
        texel = clamp(texel, 0.0, 1.0);
        @if(o_fog)
            @if(o_alpha)
                texel = vec4(mix(texel.rgb, drawU.fog_color.rgb, vFogFactor), texel.a);
            @else
                texel = mix(texel, drawU.fog_color.rgb, vFogFactor);
            @end
        @end

        @if(o_texture_edge && o_alpha)
            if (texel.a > 0.19) texel.a = 1.0; else discard;
        @end

        @if(o_alpha && o_noise)
            texel.a *= floor(clamp(random(vec3(floor(gl_FragCoord.xy * frameU.noise_scale), float(frameU.frame_count))) + texel.a, 0.0, 1.0));
        @end

        @if(o_grayscale)
            float intensity = (texel.r + texel.g + texel.b) / 3.0;
            vec3 new_texel = drawU.grayscale_color.rgb * intensity;
            texel.rgb = mix(texel.rgb, new_texel, drawU.grayscale_color.a);
        @end

        // N64 RGB framebuffer dither (per-primitive G_CD_* mode in lod_params.w)
        @if(o_alpha)
            texel.rgb = applyRdpDither(texel.rgb, drawU.lod_params.w, gl_FragCoord.xy, frameU.noise_scale, frameU.frame_count);
        @else
            texel = applyRdpDither(texel, drawU.lod_params.w, gl_FragCoord.xy, frameU.noise_scale, frameU.frame_count);
        @end

        @if(o_alpha)
            @if(o_alpha_threshold)
                if (texel.a < 8.0 / 256.0) discard;
            @end
            @if(o_invisible)
                texel.a = 0.0;
            @end
            vOutColor = texel;
        @else
            vOutColor = vec4(texel, 1.0);
        @end

        @if(o_prim_depth)
            gl_FragDepth = drawU.misc.x;
        @end
    }
@end
