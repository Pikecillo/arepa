#version 130

out vec4 frag_color;

varying vec3 col;

void main() {
    frag_color = vec4(col, 1.0);
}
