#version 330

in vec3 fragNormal;
in vec2 fragTexCoord;
in vec3 fragPos;

uniform vec3 viewPos;
uniform sampler2D ourTexture;

out vec4 outColor;

struct DirLight {
	vec3 direction;

	vec3 color;

	float ambient;
	float diffuse;
	float specular;
};

struct PointLight {
	vec3 position;
	vec3 direction;

	vec3 color;

	float ambient;
	float diffuse;
	float specular;

	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
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
};

struct Material {
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;

	float shininess;
};

#define NB_MAX_LIGHT 50

uniform DirLight dirLights[NB_MAX_LIGHT];
uniform PointLight pointLights[NB_MAX_LIGHT];
uniform SpotLight spotLights[NB_MAX_LIGHT];

uniform Material material;

uniform int nbDirLight;
uniform int nbPointLight;
uniform int nbSpotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);

	float diffuse = max(dot(lightDir, normal), 0.0)  * light.diffuse;

	vec3 haflwaydir = normalize(lightDir + viewDir);

	float spec = pow(max(dot(viewDir, haflwaydir), 0.0), material.shininess);

	float specular = spec * light.specular;

	return ((light.ambient * material.ambient) + (diffuse * material.diffuse) + (specular * material.specular)) * light.color;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	float ambient = light.ambient;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	float diffuse = light.diffuse * diff;

	vec3 haflwaydir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(viewDir, haflwaydir), 0.0), material.shininess);
	float specular = light.specular * spec;

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	diffuse  *= intensity;
	specular *= intensity;

	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return ((ambient * material.ambient) + (diffuse * material.diffuse) + (specular * material.specular)) * light.color;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	float diffuse = max(dot(lightDir, normal), 0.0) * light.diffuse * attenuation;
	vec3 haflwaydir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(viewDir, haflwaydir), 0.0), material.shininess);
	float specular = spec * light.specular * attenuation;

	return ((light.ambient * material.ambient) + (diffuse * material.diffuse) + (specular * material.specular)) * light.color;
}

void main() {
	vec3 norm = normalize(fragNormal);
	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 result = vec3(0);

	for(int i = 0; i < nbDirLight; i++)
		result += CalcDirLight(dirLights[i], norm, viewDir);

	for(int j = 0; j < nbPointLight; j++)
		result += CalcPointLight(pointLights[j], norm, fragPos, viewDir);

	//for(int k = 0; k < nbSpotLight; k++)
		//result += CalcSpotLight(spotLights[k], norm, fragPos, viewDir);

	outColor =  vec4(result, 1.0) * texture(ourTexture, fragTexCoord);
}