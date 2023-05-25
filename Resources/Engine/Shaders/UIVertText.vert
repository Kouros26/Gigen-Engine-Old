#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 ortho;
uniform mat4 model;
uniform int isWorld;

void main()
{
	if(isWorld > 0)
	{
		gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
	}
	else 
	{
		gl_Position = ortho * vec4(vertex.xy, 0.0, 1.0);
	}
    
    TexCoords = vertex.zw;
}  