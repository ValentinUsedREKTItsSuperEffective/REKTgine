// Version du GLSL

#version 330 core


// Entrées

layout (location = 0) in vec3 in_Pos;
layout (location = 1)in vec2 in_UV;
layout (location = 2)in vec3 in_Normal;


// Uniform

uniform mat4 projection;
uniform mat4 modelView;


// Sortie

out vec2 coordTexture;
out vec3 normal;


// Fonction main

void main()
{
    // Position finale du vertex en 3D

    gl_Position = projection * modelView * vec4(in_Pos, 1.0);

    // Envoi des coordonnées de texture au Fragment Shader

    coordTexture = in_UV;
    normal = in_Normal;
}
