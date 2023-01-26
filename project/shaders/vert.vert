#version 450

layout(set = 0, binding = 0) uniform UniformBufferModel {
    mat4 model;
} ubo;

layout(set = 1, binding = 0) uniform UniformBufferGlobal {
    mat4 viewProj;
    vec3 viewPos;
} uboGlobal;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragPos;
layout(location = 3) out vec3 viewPos;

void main() {
    gl_Position = uboGlobal.viewProj * ubo.model * vec4(inPosition, 1.0);
    fragNormal =  mat3(transpose(inverse(ubo.model))) * inNormal;
    fragTexCoord = inTexCoord;
    fragPos = vec3(ubo.model * vec4(inPosition, 1.0));
    viewPos = uboGlobal.viewPos;
}