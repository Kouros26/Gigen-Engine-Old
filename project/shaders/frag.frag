#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragPos;
layout(location = 3) in vec3 viewPos;

layout(set = 0, binding = 1) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

struct DirLight {
    vec3 direction;
	vec3 color;

    float ambient;
    float diffuse;
    float specular;
};

#define SHINYNESS 8

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
     float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), SHINYNESS);
    // combine results
    float ambient  = light.ambient; //* vec3(texture(texture1, TexCoords));
    float diffuse  = light.diffuse  * diff; //* vec3(texture(texture1, TexCoords));
    float specular = light.specular * spec; //* vec3(texture(texture1, TexCoords));
    return (ambient + diffuse + specular) * light.color;
}

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPos);

    DirLight light;
    light.direction = vec3(0.2, -0.5, 0.5);
    light.color = vec3(1, 1, 1);
    light.ambient = 0.2;
    light.diffuse = 0.5;
    light.specular = 0.7;

    vec3 result = CalcDirLight(light, norm, viewDir);

    outColor = texture(texSampler, fragTexCoord) * vec4(result, 1.0);
}