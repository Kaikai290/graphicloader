#version 460 core

out vec4 colour;

uniform sampler2D texture0;

in float Height;

void main()
{
  colour = vec4(vec3(Height/64.0f), 1.0f);//vec4(1.0f);
}

