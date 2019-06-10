// Version du GLSL

#version 330 core


// Entr�e

in vec2 coordTexture;

// Uniform

uniform sampler2D colorTex;
uniform vec3 color;

uniform vec3 ambientColor;

// Sortie

out vec4 outColor;

void main(){
    outColor = texture(colorTex, coordTexture) * vec4(color * ambientColor, 1);
}
