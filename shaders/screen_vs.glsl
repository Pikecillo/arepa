#version 130

in vec3 in_pos;
in vec2 in_tex;

varying vec2 v_tex;

void main() {
     v_tex = in_tex;

     gl_Position = vec4(in_pos, 1.0);
}
