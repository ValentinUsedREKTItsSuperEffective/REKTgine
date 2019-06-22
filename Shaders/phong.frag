#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Entrée
in vec3 position;
in vec3 normal;
in vec2 coordTexture;
in vec3 lightPosition;

// Uniform
uniform sampler2D colorTex;
uniform vec3 color;

uniform Material material;
uniform Light light;

// Sortie
out vec4 outColor;

void main(){
    vec3 ambient = material.ambient * light.ambient;

    vec3 N = normalize(normal);
    vec3 lightDir = normalize(lightPosition - position);
    vec3 diffuse = vec3(1.0) * material.diffuse * max(0.0, dot(lightDir, N)) * light.diffuse;

    vec3 specular = vec3(0.0f);
    if(dot(lightDir, N) >= 0.0f){
        vec3 R = reflect(-lightDir, N);
        vec3 viewDir = normalize(-position);
        float specularStrengh = 0.5;
        specular = vec3(1.0) * specularStrengh * material.specular * pow(max(0.0, dot(viewDir, R)), material.shininess) * light.specular;
    }

    outColor = vec4(light.color, 1) * texture(colorTex, coordTexture) * vec4(color * (ambient + diffuse + specular), 1);
}
