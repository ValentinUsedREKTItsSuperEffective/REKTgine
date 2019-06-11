#version 330 core

// Entrées
layout (location = 0) in vec3 in_Pos;
layout (location = 1)in vec2 in_UV;


// Uniform
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


// Sortie
out vec2 coordTexture;


void main(){
    coordTexture = in_UV;

    gl_Position = projection * view * model * vec4(in_Pos, 1.0);
}
