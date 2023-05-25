#version 330

in vec3 fragNormal;
in vec2 fragTexCoord;
in vec3 fragPos;

uniform vec3 viewPos;
uniform sampler2D ourTexture;

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

vec3 CalcDirLight(Light _light, vec3 _normal, vec3 _viewDir)
{
	vec3 lightDir = normalize(-_light.direction);

	float diffuse = max(dot(lightDir, _normal), 0.0)  * _light.diffuse;

	vec3 haflwaydir = normalize(lightDir + _viewDir);

	float spec = pow(max(dot(_viewDir, haflwaydir), 0.0), material.shininess);

	float specular = spec * _light.specular;

	return ((_light.ambient * material.ambient) + (diffuse * material.diffuse) + (specular * material.specular)) * _light.color;
}  

vec3 CalcPointLight(Light _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir)
{
	vec3 lightDir = normalize(_light.position - _fragPos);
	float dist = length(_light.position - _fragPos);
	float attenuation = 1.0 / (_light.constant + _light.linear * dist + _light.quadratic * (dist * dist));
	float diffuse = max(dot(lightDir, _normal), 0.0) * _light.diffuse * attenuation;
	vec3 haflwaydir = normalize(lightDir + _viewDir);
	float spec = pow(max(dot(_viewDir, haflwaydir), 0.0), material.shininess);
	float specular = spec * _light.specular * attenuation;

	return ((_light.ambient * material.ambient) + (diffuse * material.diffuse) + (specular * material.specular)) * _light.color;
} 

vec3 CalcSpotLight(Light _light, vec3 _normal, vec3 _fragPos, vec3 _viewDir)
{
	vec3 lightDir = normalize(_light.position - _fragPos);
	float dist = length(_light.position - _fragPos);
	float attenuation = 1.0 / (_light.constant + _light.linear * dist + _light.quadratic * (dist * dist));
	float diffuse = max(dot(lightDir, _normal), 0.0) * _light.diffuse * attenuation;
	vec3 haflwaydir = normalize(lightDir + _viewDir);
	float spec = pow(max(dot(_viewDir, haflwaydir), 0.0), material.shininess);
	float specular = spec * _light.specular * attenuation;

	//spot part
	float theta = dot(lightDir, normalize(-_light.direction));
	float epsilon = (_light.cutOff - _light.outerCutOff);
	float intensity = clamp((theta - _light.outerCutOff) / epsilon, 0.0, 1.0);
	float ambient = _light.ambient * intensity;
	diffuse *= intensity;
	specular *= intensity;

	return ((ambient * material.ambient) + (diffuse * material.diffuse) + (specular * material.specular)) * _light.color;
}

vec3 CalcLight(Light _light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	if(_light.type == 0)
	{
		return CalcDirLight(_light, normal, viewDir);
	}
	if(_light.type == 1)
	{
		return CalcPointLight(_light, normal, fragPos, viewDir);
	}
	if(_light.type == 2)
	{
		return CalcSpotLight(_light, normal, fragPos, viewDir);
	}
}

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result;
	
	for(int i = 0; i < nbLights; i++)
		result += CalcLight(lights[i], norm, fragPos, viewDir);

	outColor = vec4(result, 1.0) * texture(ourTexture, fragTexCoord);
}