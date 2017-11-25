#version 130

in vec3 in_pos;
in vec3 in_nor;

uniform mat4 u_vmatrix;
uniform mat4 u_pmatrix;

varying vec3 col;

void main() {
     col = abs(in_nor);

     gl_Position = u_pmatrix * u_vmatrix * vec4(in_pos, 1.0);
}
