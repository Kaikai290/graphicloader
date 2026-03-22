
#version 460 core

out vec4 colour;

in vec4 vertexColour;

void main()
{
  colour = vertexColour;
}
