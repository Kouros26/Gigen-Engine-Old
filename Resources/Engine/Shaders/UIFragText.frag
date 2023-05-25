#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform int isImage;
uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
	if(isImage > 0)
	{
		color = vec4(textColor, 1.0) * texture(text, TexCoords);
	}
	else 
	{
		vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    		color = vec4(textColor, 1.0) * sampled;
	}
    
}   