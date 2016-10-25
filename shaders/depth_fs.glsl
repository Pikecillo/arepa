#version 130

out vec4 frag_color;
out vec3 frag_pos;
out vec3 frag_normal;

varying vec3 v_pos;
varying vec3 v_nor;

void main() {
     frag_color = vec4(1.0, 1.0, 1.0, 1.0);
     frag_pos = v_pos;
     frag_normal = v_nor;
}
