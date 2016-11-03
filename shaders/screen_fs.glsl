#version 130

out vec4 frag_color;

uniform sampler2D u_albedo_texture;
uniform sampler2D u_nor_texture;
uniform sampler2D u_pos_texture;
uniform vec3 u_light;

varying vec2 v_tex;

void main() {
    vec3 position = texture(u_pos_texture, v_tex).xyz;
    vec3 normal = texture(u_nor_texture, v_tex).xyz;
    vec3 L = normalize(u_light - position);
    vec4 albedo = texture(u_albedo_texture, v_tex);    

    frag_color = dot(L, -normal) * albedo;
}