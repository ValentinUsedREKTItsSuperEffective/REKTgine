#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 2) in vec3 inNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 position;
out vec3 normal;

void main(){
    position = vec3(model * vec4(inPos, 1.0));
    gl_Position = projection * view * model * vec4(inPos, 1.0);

    // TODO : Move the expensive inverse operation out of the shader
    normal = mat3(transpose(inverse(model))) * inNormal;
}
