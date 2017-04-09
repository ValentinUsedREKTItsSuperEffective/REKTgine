// Version du GLSL

#version 330 core


// Entrées

in vec3 in_Vertex;


// Uniform

uniform mat4 projection;
uniform mat4 modelView;


// Fonction main

void main()
{
    // Position finale du vertex en 3D
    gl_Position = projection * modelView * vec4(in_Vertex, 1.0);
}
