#version 330 core

out vec4 fragColor;

in vec3 position;
in vec3 normal;

uniform vec3 cameraPosition;
uniform samplerCube skybox;

uniform float refractiveIndex;

vec3 Reflect(){
    vec3 I = normalize(position - cameraPosition);
    vec3 N = normalize(normal);
    return reflect(I, N);
}

vec3 Refract(){
    float ratio = 1.00 / refractiveIndex; // consider that the upper refractiveIndex is Air
    vec3 I = normalize(position - cameraPosition);
    vec3 N = normalize(normal);
    return refract(I, N, ratio);
}

void main(){
    vec3 R;
    if(refractiveIndex == 0.0){
        R = Reflect();
    } else {
        R = Refract();
    }
    fragColor = vec4(texture(skybox, R).rgb, 1.0);
}
