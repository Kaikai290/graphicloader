#version 460 core

out vec4 colour;

in vec2 texCoords;

uniform sampler2D texture0;

vec4 quadratic_bezier(vec4 A, vec4 B, vec4 C, float t) {
  vec4 D = mix(A, B, t);

  vec4 E = mix(B, C, t);

  vec4 P = mix(D, E, t);

  return P;
}

layout(binding = 0) uniform area_block {
  uint counterValue;
};

int max_area = 1;

int foo();

void main()
{
  float space = clamp(float(counterValue)+float(max_area), 0.0, 1.0);
  foo();

  colour = texture(texture0, texCoords);
}
