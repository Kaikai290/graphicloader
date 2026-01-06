#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoord;

out vec4 vertexColour;
out vec2 texCoords;
// IT IS STORED IN COLUMN MAJOR FORMAT :))))))))))))))
mat4 move = mat4 (
1.0, 0.0, 0.0, 0.0,
0.0, 1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0);

vec4 shift = vec4(
0.0,
0.0,
0.0,
0.0);

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
   gl_Position =  projection * view * model * vec4(aPos, 1.0);
   texCoords = texCoord;
   //gl_Position  = move * vec4(aPos, 1.0);
}
