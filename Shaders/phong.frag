#version 330 core

// Entrée
in vec3 position;
in vec3 normal;
in vec2 coordTexture;

// Uniform
uniform sampler2D colorTex;
uniform vec3 color;

uniform vec3 ambientColor;
uniform float ambientIntensity;

// Sortie
out vec4 outColor;

void main(){
    outColor = texture(colorTex, coordTexture) * vec4(color * ambientColor, 1) * ambientIntensity;
}
