#version 460 core
layout (location = 0) in vec3 vertices;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec3 position;
layout (location = 3) in vec3 velocity;


out vec3 vertexColour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

mat4 planeDirection(vec3 forward, vec3 up) {
  vec3 side = cross(forward, up);
  vec3 u_frame = cross(side, forward);
  return mat4(vec4(side, 0.0f),
              vec4(u_frame, 0.0f),
              vec4(forward, 0.0f),
              vec4(vec3(0.0f), 1.0f));
}

vec3 pickColour(float f)
{
float R = sin(f * 6.2831853);
float G = sin((f + 0.3333) * 6.2831853);
float B = sin((f + 0.6666) * 6.2831853);
return vec3(R, G, B) * 0.25 + vec3(0.75);
}


void main() {
  mat4 lookat = planeDirection(normalize(velocity), vec3(0.0f, 1.0f, 0.0f));

  vec4 planeCoords = lookat * vec4(vertices.xyz, 1.0);
  gl_Position =  projection * view * model * (planeCoords + vec4(position, 0.0));

  vec3 N = mat3(lookat) * normals;
  vec3 C = pickColour(fract(float(gl_InstanceID/float(1237.0))));

  vertexColour = mix(C*0.2, C, smoothstep(0.0,0.8,abs(N).z));
}
