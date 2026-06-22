@prism(type='hlsl', name='Fast3D HLSL sRGB Post', version='1.0.0', description='Final-pass linear->sRGB (gamma) output encoding', author='Fast3D')

@if(o_root_signature)
    #define RS "RootFlags(ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | DENY_VERTEX_SHADER_ROOT_ACCESS), CBV(b0, visibility = SHADER_VISIBILITY_PIXEL), DescriptorTable(SRV(t0), visibility = SHADER_VISIBILITY_PIXEL), DescriptorTable(Sampler(s0), visibility = SHADER_VISIBILITY_PIXEL)"
@end

struct PSInput {
    float4 position : SV_POSITION;
    @{update_floats(1)} // aMtxSlot vertex attribute (matrix palette index)
    float2 uv0 : TEXCOORD0;
    @{update_floats(2)}
};

// Mirrors struct TransformUniforms in gfx_rendering_api.h
cbuffer TransformCB : register(b4) {
    float4 mtx_palette[32]; // 4 float4 rows per slot
    float4 y_scale;
}

// Per-draw constants; layout must mirror struct PerDrawCB in gfx_direct3d_common.h.
// Only uv_transform is read here, but the full layout is required so the
// register offsets line up with what the backend binds at b1.
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
    float4 lod_params;
    float4 uCustom[16];
}

Texture2D g_texture0 : register(t0);
SamplerState g_sampler0 : register(s0);

PSInput VSMain(float4 position : POSITION, float mtxSlot : MTXSLOT, float2 uv0 : TEXCOORD0) {
    PSInput result;

    // RSP position transform: matrix palette entry selected per vertex
    int mtxBase = int(mtxSlot + 0.5) * 4;
    float4 clipPos = position.x * mtx_palette[mtxBase] + position.y * mtx_palette[mtxBase + 1] +
                     position.z * mtx_palette[mtxBase + 2] + position.w * mtx_palette[mtxBase + 3];

    // D3D clip space: z in 0..1; y flip is carried in the uniform
    result.position = float4(clipPos.x, clipPos.y * y_scale.x, (clipPos.z + clipPos.w) / 2.0, clipPos.w);
    // Tile shift/origin/bilerp/size pipeline folded into one transform
    result.uv0 = float2(uv0.x * uv_transform[0].x + uv_transform[0].y,
                        uv0.y * uv_transform[0].z + uv_transform[0].w);
    return result;
}

@if(o_root_signature)
    [RootSignature(RS)]
@end

// Linear -> sRGB transfer (the gamma boost previously baked into every fragment
// shader via srgb_mode; now applied once as a fullscreen pass).
float4 fromLinear(float4 linearRGB){
    bool3 cutoff = linearRGB.rgb < float3(0.0031308, 0.0031308, 0.0031308);
    float3 higher = 1.055 * pow(linearRGB.rgb, float3(1.0 / 2.4, 1.0 / 2.4, 1.0 / 2.4)) - float3(0.055, 0.055, 0.055);
    float3 lower = linearRGB.rgb * float3(12.92, 12.92, 12.92);
    return float4(lerp(higher, lower, cutoff), linearRGB.a);
}

struct PSOutput {
    float4 color : SV_TARGET;
};

PSOutput PSMain(PSInput input, float4 screenSpace : SV_Position) {
    float4 texel = g_texture0.Sample(g_sampler0, input.uv0);
    PSOutput output;
    output.color = fromLinear(float4(texel.rgb, 1.0));
    return output;
}
