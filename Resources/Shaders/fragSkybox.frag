#version 330

in vec2 fragTexCoord;

uniform sampler2D ourTexture;

out vec4 outColor;

void main() {
	outColor = texture(ourTexture, fragTexCoord);
}