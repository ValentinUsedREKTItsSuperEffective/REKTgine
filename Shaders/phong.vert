#version 330 core

// Entrées
layout (location = 0) in vec3 in_Pos;
layout (location = 1)in vec2 in_UV;
layout (location = 2)in vec3 in_Normal;


// Uniform
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


// Sortie
out vec3 position;
out vec2 coordTexture;
out vec3 normal;

void main(){
    position = model * vec4(in_Pos, 1.0);
    coordTexture = in_UV;
    normal = in_Normal;

    gl_Position = projection * view * position;
}
