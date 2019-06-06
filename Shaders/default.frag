// Version du GLSL

#version 330 core


// Entrée

in vec2 coordTexture;

// Uniform

uniform sampler2D tex;
uniform vec3 color;


// Sortie

out vec4 out_Color;

void main(){
    out_Color = texture(tex, coordTexture) * vec4(color, 1);
}
