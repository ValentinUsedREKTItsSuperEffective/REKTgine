// Version du GLSL

#version 330 core


// Entrée

in vec2 coordTexture;
in vec3 normal;


// Uniform

uniform sampler2D tex;

uniform vec3 lightColor;


// Sortie

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixel

    out_Color = texture(tex, coordTexture) * vec4(lightColor, 1);
}
