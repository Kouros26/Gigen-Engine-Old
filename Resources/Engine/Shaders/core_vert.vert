#version 460

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec4 boneIds; 
layout(location = 4) in vec4 weights;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

out vec3 fragNormal;
out vec2 fragTexCoord;
out vec3 fragPos;
out vec3 fragViewPos;

uniform mat4 model;
uniform mat4 viewProj;

void main() {

    vec4 totalPosition = vec4(0.0f);
    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
		int id = int(boneIds[i]);
        if(id == -1) 
            continue;
        if(id >= MAX_BONES) 
        {
            totalPosition = vec4(inPosition,1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[id] * vec4(inPosition,1.0f);
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(finalBonesMatrices[id]) * inNormal;
    }
	
	if(totalPosition == vec4(0.0f))
		totalPosition = vec4(inPosition,1.0f);
	
    gl_Position = viewProj * model * totalPosition;
    fragNormal =  mat3(transpose(inverse(model))) * inNormal;
    fragTexCoord = inTexCoord;
    fragPos = vec3(model * vec4(inPosition, 1.0));
}