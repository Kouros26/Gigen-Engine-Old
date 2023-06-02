#version 460

in vec3 fragNormal;
in vec2 fragTexCoord;
in vec3 fragPos;
in vec4 FragPosLightSpace;

uniform vec3 viewPos;
layout(binding = 0) uniform sampler2D ourTexture;
layout(binding = 1) uniform sampler2D shadowMap;

out vec4 outColor;

struct Light
{
	vec3 position;
	vec3 direction;

	vec3 color;

	float ambient;
	float diffuse;
	float specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;

	int type;
};

struct Material {
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;

	float shininess;
};

#define NB_MAX_LIGHT 50

uniform Light lights[NB_MAX_LIGHT];

uniform Material material;

uniform int nbLights;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    float bias = 0.005;
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

vec3 CalcDirLight(Light _light, vec3 _normal, vec3 _viewDir, float _shadow)
{
	vec3 lightDir = normalize(-_light.direction);

	float diffuse = max(dot(lightDir, _normal), 0.0)  * _light.diffuse;

	vec3 haflwaydir = normalize(lightDir + _viewDir);

	float spec = pow(max(dot(_viewDir, haflwaydir), 0.0), material.shininess);

	float specular = spec * _light.specular;

	//diffuse *= (1.0 - _shadow);
	//specular *= (1.0 - _shadow);

	return ((_light.ambient * material.ambient) + (diffuse * material.diffuse) + (specular * material.specular)) * _light.color;
}

vec3 CalcPointLight(Light _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir, float _shadow)
{
	vec3 lightDir = normalize(_light.position - _fragPos);
	float dist = length(_light.position - _fragPos);
	float attenuation = 1.0 / (_light.constant + _light.linear * dist + _light.quadratic * (dist * dist));
	float diffuse = max(dot(lightDir, _normal), 0.0) * _light.diffuse * attenuation;
	vec3 haflwaydir = normalize(lightDir + _viewDir);
	float spec = pow(max(dot(_viewDir, haflwaydir), 0.0), material.shininess);
	float specular = spec * _light.specular * attenuation;

	//diffuse *= (1.0 - _shadow);
	//specular *= (1.0 - _shadow);

	return ((_light.ambient * material.ambient) + (diffuse * material.diffuse) + (specular * material.specular)) * _light.color;
}

vec3 CalcSpotLight(Light _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir, float _shadow)
{
	float ambient = _light.ambient;

	vec3 norm = normalize(_normal);
	vec3 lightDir = normalize(_light.position - _fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	float diffuse = _light.diffuse * diff;

	vec3 haflwaydir = normalize(lightDir + _viewDir);
	float spec = pow(max(dot(_viewDir, haflwaydir), 0.0), material.shininess);
	float specular = _light.specular * spec;

	float theta = dot(lightDir, normalize(-_light.direction));
	float epsilon = (_light.cutOff - _light.outerCutOff);
	float intensity = clamp((theta - _light.outerCutOff) / epsilon, 0.0, 1.0);
	diffuse  *= intensity;
	specular *= intensity;

	return ((ambient * material.ambient) + (diffuse * material.diffuse) + (specular * material.specular)) * _light.color;
}

vec3 CalcLight(Light _light, vec3 normal, vec3 fragPos, vec3 viewDir, float _shadow)
{
	if(_light.type == 0)
	{
		return CalcDirLight(_light, normal, viewDir, _shadow);
	}
	if(_light.type == 1)
	{
		return CalcPointLight(_light, normal, fragPos, viewDir, _shadow);
	}
	if(_light.type == 2)
	{
		return CalcSpotLight(_light, normal, fragPos, viewDir, _shadow);
	}
}

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result;
	float shadow = ShadowCalculation(FragPosLightSpace);

	for(int i = 0; i < nbLights; i++)
		result += CalcLight(lights[i], norm, fragPos, viewDir, shadow);

	if(shadow > 0)
		result /= 2;

	outColor = vec4(result, 1.0)  * texture(ourTexture, fragTexCoord);
}