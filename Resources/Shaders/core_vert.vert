#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

out vec3 fragNormal;
out vec2 fragTexCoord;
out vec3 fragPos;
out vec3 fragViewPos;

uniform mat4 model;
uniform mat4 viewProj;

void main() {
    gl_Position = viewProj * model * vec4(inPosition, 1.0);
    fragNormal =  mat3(transpose(inverse(model))) * inNormal;
    fragTexCoord = inTexCoord;
    fragPos = vec3(model * vec4(inPosition, 1.0));
}