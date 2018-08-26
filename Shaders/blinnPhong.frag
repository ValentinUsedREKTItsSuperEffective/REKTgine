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


// Fonctions

vec3 Phong() {
    float ambientIntensity = 0.1f;
    vec3 ambientColor = vec3(0.8f, 0.8f, 0.7f);

    vec3 ambient = ambientIntensity * ambientColor;

    return ambient;
}

void main()
{
    // Couleur du pixel
    out_Color = texture(tex, coordTexture) * vec4(Phong(), 1);
}
