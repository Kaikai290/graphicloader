#version 460 core
layout (location = 0) in vec3 Vertex;

out vec4 vertexColour;
out float green;

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 view;

uniform mat4 projection;

int random(int seed, int iter) {

  int value = seed;
  int i = 0;

  for(i = 0; i != iter; i++) {
    value = ((value << 13) ^ (value >> 5)) * 15485863;
  }
  
  return value;
}

void main() {
  int x = gl_InstanceID >> 10;
  int y = gl_InstanceID >> 10;
  int z = gl_InstanceID  & 0x3FF;
  int xOffset = random(gl_InstanceID, 4);
  int yOffset = random(gl_InstanceID, 11);
  int zOffset = random(gl_InstanceID, 7);
  mat4 vModel = model;
  float cosTheta = sin((float(xOffset&0xFF)/256.0) * 6.28);
  float sinTheta = cos((float(xOffset&0xFF)/256.0) * 6.28);
  mat4 rotation = mat4(vec4(cosTheta, 0.0, sinTheta, 0.0), vec4(0.0, 1.0, 0.0, 0.0), vec4(-sinTheta, 0.0, cosTheta, 0.0), vec4(0.0, 0.0, 0.0, 1.0));
  vModel[3][0] =  ((x - 512)/2) + (float(xOffset & 0xFF)/256.0);
  vModel[3][2] =  ((512 - z)/2) + (float(zOffset & 0xFF)/256.0);
  vModel[1][1] = vModel[1][1] * clamp((float(yOffset & 0xFF)/256.0), 0.6, 1.0);
  vModel = rotation * vModel;
   gl_Position =  projection * view * vModel * vec4(Vertex, 1.0);
  green = xOffset/256.0;
}
