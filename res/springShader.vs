#version 460 core

layout (location = 0) in vec4 pos_mass;

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 view;

uniform mat4 projection;

out vec4 massColour;


void main() {
   gl_Position =  projection * view * model * vec4(pos_mass.xyz, 1.0); 
   massColour = vec4(pos_mass.www, 1.0f);
}
