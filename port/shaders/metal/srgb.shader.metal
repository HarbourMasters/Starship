@prism(type='metal', name='Fast3D Metal sRGB Post', version='1.0.0', description='Final-pass linear->sRGB (gamma) output encoding', author='Fast3D')

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
};

// Mirrors struct TransformUniforms in gfx_rendering_api.h
struct TransformUniforms {
    float4 mtx_palette[32]; // 4 float4 rows per slot
    float4 y_scale;
};

struct FragOut {
    float4 color [[color(0)]];
};

struct Vertex {
    float4 position [[attribute(@{get_vertex_index()})]];
    @{update_floats(4)}
    float mtxSlot [[attribute(@{get_vertex_index()})]];
    @{update_floats(1)}
    float2 texCoord0 [[attribute(@{get_vertex_index()})]];
    @{update_floats(2)}
};

struct ProjectedVertex {
    float2 texCoord0;
    float4 position [[position]];
};

vertex ProjectedVertex vertexShader(Vertex in [[stage_in]]
    , constant DrawUniforms& drawUniforms [[buffer(2)]]
    , constant TransformUniforms& transformUniforms [[buffer(3)]]
) {
    ProjectedVertex out;

    // RSP position transform: matrix palette entry selected per vertex
    int mtxBase = int(in.mtxSlot + 0.5) * 4;
    float4 clipPos = in.position.x * transformUniforms.mtx_palette[mtxBase] +
                     in.position.y * transformUniforms.mtx_palette[mtxBase + 1] +
                     in.position.z * transformUniforms.mtx_palette[mtxBase + 2] +
                     in.position.w * transformUniforms.mtx_palette[mtxBase + 3];

    // Tile shift/origin/bilerp/size pipeline folded into one transform
    out.texCoord0 = float2(in.texCoord0.x * drawUniforms.uv_transform[0].x + drawUniforms.uv_transform[0].y,
                           in.texCoord0.y * drawUniforms.uv_transform[0].z + drawUniforms.uv_transform[0].w);

    out.position = float4(clipPos.x, clipPos.y * transformUniforms.y_scale.x, (clipPos.z + clipPos.w) / 2.0, clipPos.w);
    return out;
}
// END - BEGIN FRAGMENT SHADER

// Linear -> sRGB transfer (the gamma boost previously applied via an sRGB
// framebuffer pixel format; now applied once as a fullscreen pass).
float4 fromLinear(float4 linearRGB) {
    bool3 cutoff = linearRGB.rgb < float3(0.0031308);
    float3 higher = float3(1.055) * pow(linearRGB.rgb, float3(1.0 / 2.4)) - float3(0.055);
    float3 lower = linearRGB.rgb * float3(12.92);
    return float4(mix(higher, lower, float3(cutoff)), linearRGB.a);
}

fragment FragOut fragmentShader(
    ProjectedVertex in [[stage_in]],
    constant FrameUniforms &frameUniforms [[buffer(0)]],
    constant DrawUniforms &drawUniforms [[buffer(1)]]
    , texture2d<float> uTex0 [[texture(0)]], sampler uTex0Smplr [[sampler(0)]]
) {
    float4 texel = uTex0.sample(uTex0Smplr, in.texCoord0);
    FragOut out;
    out.color = fromLinear(float4(texel.rgb, 1.0));
    return out;
}
