// Version du GLSL

#version 330 core


// Entrées

in vec3 in_Vertex;
in vec2 in_TexCoord0;
in vec3 in_Normal;


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

    gl_Position = projection * modelView * vec4(in_Vertex, 1.0);

    // Envoi des coordonnées de texture au Fragment Shader

    coordTexture = in_TexCoord0;
    normal = in_Normal;
}
