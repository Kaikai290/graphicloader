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

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 view;
uniform mat4 projection;

vec4 quadratic_bezier(vec4 A, vec4 B, vec4 C, float t) {
  vec4 D = mix(A, B, t);

  vec4 E = mix(B, C, t);

  vec4 P = mix(D, E, t);

  return P;
}

void main() {
   mat4 modelMove = model;
   modelMove[3][0] = modelMove[3][0] + (10 * gl_InstanceID);
   gl_Position =  projection * view * modelMove * vec4(aPos, 1.0);
   texCoords = texCoord;
   //gl_Position  = move * vec4(aPos, 1.0);
}
