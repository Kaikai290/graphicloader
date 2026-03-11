
#version 460 core

out vec4 fragColour;
in float green;


void main()
{
  float grass = clamp(green, 0.6f, 1.0f);
	fragColour = vec4(0.0f, grass, 0.4f, 1.0f);
}
