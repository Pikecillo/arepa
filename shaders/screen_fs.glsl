#version 130

out vec4 frag_color;

uniform sampler2D u_texture;

varying vec2 v_tex;

void main() {
    frag_color = texture(u_texture, v_tex);
}