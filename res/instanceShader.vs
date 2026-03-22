#version 460 core

layout (location = 0) in vec3 vert;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec4 pos;

out vec4 vertexColour;

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 view;
uniform mat4 projection;


void main() {
   mat4 vModel = model;
   vModel[3] = pos;
   gl_Position =  projection * view * vModel * vec4(vert, 1.0); 
  vertexColour = colour;
}
