#version 330 core

struct Material {
    sampler2D map;
    vec3 color;

    vec3 ambient;

    sampler2D specularMap;
    vec3 specular;
    float shininess;

    sampler2D emissiveMap;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight {
    vec3 direction;
};

// Entr�e
in vec3 position;
in vec3 normal;
in vec2 coordTexture;

// Uniform
uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;
uniform DirectionalLight directionalLight;

// Sortie
out vec4 outColor;

vec3 computeDirectionalLightComponents(){
    vec3 color = material.color * texture(material.map, coordTexture).rgb;
    vec3 ambient = color * material.ambient * light.ambient;

    vec3 N = normalize(normal);
    // vec3 lightDir = normalize(light.position - position);
    vec3 lightDir = normalize(-directionalLight.direction);
    vec3 diffuse = color * max(0.0, dot(lightDir, N)) * light.diffuse;

    vec3 specular = vec3(0.0f);
    if(dot(lightDir, N) >= 0.0f){
        vec3 R = reflect(-lightDir, N);
        vec3 viewDir = normalize(cameraPosition - position);
        specular = material.specular * texture(material.specularMap, coordTexture).rgb * pow(max(0.0, dot(viewDir, R)), material.shininess) * light.specular;
    }

    return ambient + diffuse + specular;
}

void main(){

    vec3 dirComponents = computeDirectionalLightComponents();

    vec3 emissive = texture(material.emissiveMap, coordTexture).rgb;

    outColor = vec4((dirComponents + emissive), 1);
}
