#version 330 core

// Entrées
layout (location = 0) in vec3 in_Pos;
layout (location = 1) in vec2 in_UV;
layout (location = 2) in vec3 in_Normal;


// Uniform
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 vLightPosition;

// Sortie
out vec3 position;
out vec2 coordTexture;
out vec3 normal;
out vec3 lightPosition;

void main(){
    position = vec3(view * model * vec4(in_Pos, 1.0));
    coordTexture = in_UV;
    // TODO : Move the expensive inverse operation out of the shader
    normal = mat3(transpose(inverse(view * model))) * in_Normal;
    lightPosition = vec3(view * vec4(vLightPosition, 1.0));

    gl_Position = projection * view * model * vec4(in_Pos, 1.0);
}
