#version 460 core

layout (location = 0) in vec4 pos_mass;
layout (location = 1) in vec3 velocity;
layout (location = 2) in ivec4 connections;

layout (binding = 0) uniform samplerBuffer tex_position;

out vec4 tfPos_mass;
out vec3 tfVelocity;

uniform float t = 0.7;

uniform float k = 2000;

const vec3 gravity = vec3(0.0, -9.8, 0.0);

uniform float c = 2.8;

uniform float rest_length = 0.88;


void temp() {
  int count = 0;
  for(int i = 0; i != 4; i++) {
    if(connections.x == -1) {
      tfPos_mass = vec4(pos_mass.xyz, 0.0);
  tfVelocity = vec3(0.0f);
      return;
    } 
    else {
    tfPos_mass = vec4(pos_mass.xyz, 1.0);
  tfVelocity = vec3(0.0f);
    return;
    }
  }

  tfPos_mass = vec4(pos_mass.xyz, 1.0);

}

void main() {
    vec3 p = pos_mass.xyz;
    float m = pos_mass.w;
    vec3 u = velocity;
    vec3 F = gravity * m - c * u;
    bool fixed_node = true;

    for(int i = 0; i != 4; i++) {
      if(int(connections[i]) != -1) {
        vec3 q = texelFetch(tex_position, connections[i]).xyz;
        vec3 d =  q - p;
        float x = length(d);
        F += -k * (rest_length - x) * normalize(d);
        fixed_node = false;
      }
    }

    if(fixed_node) {
      F = vec3(0.0);
    }

    vec3 a = F/m;

    vec3 s = u * t + 0.5 * a * t * t;
    vec3 v = u + a * t;

    s = clamp(s, vec3(-0.25), vec3(0.25));
    tfPos_mass = vec4(p + s, 0.2);
    tfVelocity =  v; 
}
