#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
layout(location = 0) out vec3 fragColor;

layout(set = 0, binding = 0) uniform vpUniformBufferObject {
    mat4 viewproj;
} viewproj_ubo;

layout(set = 1, binding = 0) uniform mUniformBufferObject {
    mat4 model;
} model_ubo;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    gl_Position = viewproj_ubo.viewproj * model_ubo.model * vec4(inPosition, 1.0);
    fragColor = inColor;
}