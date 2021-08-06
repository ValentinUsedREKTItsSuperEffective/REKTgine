#version 330 core

out vec4 fragColor;

in vec3 position;
in vec3 normal;

uniform vec3 cameraPosition;
uniform samplerCube skybox;

void main(){
    vec3 I = normalize(position - cameraPosition);
    vec3 N = normalize(normal);
    vec3 R = reflect(I, N);
    fragColor = vec4(texture(skybox, R).rgb, 1.0);
}
