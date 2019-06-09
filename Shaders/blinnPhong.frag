// Version du GLSL

#version 330 core


// Entrée

in vec2 coordTexture;

// Uniform

uniform sampler2D colorTex;
uniform vec3 color;

uniform vec3 ambientColor;

// Sortie

out vec4 out_Color;

void main(){
    out_Color = texture(colorTex, coordTexture) * vec4(color * ambientColor, 1);
}
