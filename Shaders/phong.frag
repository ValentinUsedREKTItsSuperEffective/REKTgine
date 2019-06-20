#version 330 core

// Entrée
in vec3 position;
in vec3 normal;
in vec2 coordTexture;
in vec3 lightPosition;

// Uniform
uniform sampler2D colorTex;
uniform vec3 color;

uniform vec3 ambientColor;
uniform float ambientIntensity;

// Sortie
out vec4 outColor;

void main(){
    vec3 ambient = ambientColor * ambientIntensity;

    // TODO : Use a light color for  the diffuse and specular components
    vec3 N = normalize(normal);
    vec3 lightDir = normalize(lightPosition - position);
    vec3 diffuse = vec3(1.0) * max(0.0, dot(lightDir, N));

    vec3 specular = vec3(0.0f);
    if(dot(lightDir, N) >= 0.0f){
        vec3 R = reflect(-lightDir, N);
        vec3 viewDir = normalize(-position);
        float specularStrengh = 0.5;
        float shininess = 256;
        specular = vec3(1.0) * specularStrengh * pow(max(0.0, dot(viewDir, R)), shininess);
    }

    outColor = texture(colorTex, coordTexture) * vec4(color * (ambient + diffuse + specular), 1);
}
