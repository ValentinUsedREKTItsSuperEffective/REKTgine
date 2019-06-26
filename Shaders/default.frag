#version 330 core

struct Material {
    sampler2D map;
    vec3 color;
};

// Entrée
in vec2 coordTexture;

// Uniform
uniform Material material;

// Sortie
out vec4 out_Color;

void main(){
    out_Color = texture(material.map, coordTexture) * vec4(material.color, 1);
}
