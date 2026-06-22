@prism(type='fragment', name='Fast3D Vulkan sRGB Post', version='1.0.0', description='Final-pass linear->sRGB (gamma) output encoding', author='Fast3D')

#version 450
@include("shaders/vulkan/include/common.glsli")

@if(VERTEX_SHADER)
    @include("shaders/vulkan/include/fast3d_vs.glsli")

@else
    layout(location = 0) out vec4 vOutColor;
    layout(location = 0) in vec2 vTexCoord0;

    layout(set = 1, binding = 0) uniform sampler2D uTex0;

    // Linear -> sRGB transfer (the gamma boost previously baked into every
    // fragment shader via srgb_mode; now applied once as a fullscreen pass).
    vec4 fromLinear(vec4 linearRGB) {
        bvec3 cutoff = lessThan(linearRGB.rgb, vec3(0.0031308));
        vec3 higher = vec3(1.055) * pow(linearRGB.rgb, vec3(1.0 / 2.4)) - vec3(0.055);
        vec3 lower = linearRGB.rgb * vec3(12.92);
        return vec4(mix(higher, lower, cutoff), linearRGB.a);
    }

    void main() {
        vec4 texel = texture(uTex0, vTexCoord0);
        vOutColor = fromLinear(vec4(texel.rgb, 1.0));
    }
@end
