#version 460 core
layout (location = 0) in vec3 aPos;

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 view;
uniform mat4 projection;

out vec2 texCoords;

uniform float tiling = 20.0f;


uniform float width;
uniform float height; 

void main() {
  int xScale = int(width/tiling);
  int zScale = int(height/tiling); //cast to an int to stop precision errors!
  mat4 scale = mat4(vec4(xScale , 0.0f, 0.0f, 0.0f),
                    vec4(0.0f, 1.0f, 0.0f, 0.0f),
                    vec4(0.0f, 0.0f, zScale, 0.0f),
                    vec4(0.0f, 0.0f, 0.0f, 1.0f));
  mat4 modelMove = model * scale;
  
   modelMove[3][0] = modelMove[3][0] + (xScale * (gl_InstanceID / int(tiling))) - width/2;
   modelMove[3][2] = modelMove[3][2] + (zScale * (gl_InstanceID % int(tiling))) - height/2;
   float texX = (float((gl_InstanceID / int(tiling)))+aPos.x)/(tiling);
   float texZ = (float((gl_InstanceID % int(tiling)))+aPos.z)/(tiling);
   texCoords = vec2(texX, texZ);
   gl_Position =  modelMove * vec4(aPos, 1.0);
}
