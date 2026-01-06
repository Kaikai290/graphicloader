#version 460 core

out vec4 fragColour;

in vec2 texCoords;

uniform sampler2D texture0;

void main()
{
	//fragColour = vec4(1.0f, 0.0f, 0.4f, 1.0f);
	fragColour = texture(texture0, texCoords).rgba;
}
