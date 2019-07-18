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
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Spotlight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 direction;
    float cutAngle;
    float outAngle;
};

// Entrée
in vec3 position;
in vec3 normal;
in vec2 coordTexture;

// Uniform
uniform vec3 cameraPosition;
uniform Material material;
uniform Light light;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform Spotlight spotlight;

// Sortie
out vec4 outColor;

vec3 computeDirectionalLightComponents(){
    vec3 color = material.color * texture(material.map, coordTexture).rgb;
    vec3 ambient = color * material.ambient * directionalLight.ambient;

    vec3 N = normalize(normal);
    vec3 lightDir = normalize(-directionalLight.direction);
    vec3 diffuse = color * max(0.0, dot(lightDir, N)) * directionalLight.diffuse;

    vec3 specular = vec3(0.0f);
    if(dot(lightDir, N) >= 0.0f){
        vec3 R = reflect(-lightDir, N);
        vec3 viewDir = normalize(cameraPosition - position);
        specular = material.specular * texture(material.specularMap, coordTexture).rgb * pow(max(0.0, dot(viewDir, R)), material.shininess) * directionalLight.specular;
    }

    return ambient + diffuse + specular;
}

vec3 computePointLightComponents(){
    float dist = length(light.position - position);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * dist * dist);

    vec3 color = material.color * texture(material.map, coordTexture).rgb;
    vec3 ambient = color * material.ambient * pointLight.ambient;

    vec3 N = normalize(normal);
    vec3 lightDir = normalize(light.position - position);
    vec3 diffuse = color * max(0.0, dot(lightDir, N)) * pointLight.diffuse;

    vec3 specular = vec3(0.0f);
    if(dot(lightDir, N) >= 0.0f){
        vec3 R = reflect(-lightDir, N);
        vec3 viewDir = normalize(cameraPosition - position);
        specular = material.specular * texture(material.specularMap, coordTexture).rgb * pow(max(0.0, dot(viewDir, R)), material.shininess) * pointLight.specular;
    }

    return (ambient + diffuse + specular) * attenuation;
}

vec3 computeSpotlightComponents(){
    vec3 nonNormalizedLightDir = light.position - position;
    vec3 lightDir = normalize(nonNormalizedLightDir);

    float dist = length(nonNormalizedLightDir);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * dist * dist);

    vec3 color = material.color * texture(material.map, coordTexture).rgb;
    vec3 ambient = color * material.ambient * spotlight.ambient;

    vec3 contribution = ambient * attenuation;

    vec3 N = normalize(normal);
    vec3 diffuse = color * max(0.0, dot(lightDir, N)) * spotlight.diffuse;

    vec3 specular = vec3(0.0f);
    if(dot(lightDir, N) >= 0.0f){
        vec3 R = reflect(-lightDir, N);
        vec3 viewDir = normalize(cameraPosition - position);
        specular = material.specular * texture(material.specularMap, coordTexture).rgb * pow(max(0.0, dot(viewDir, R)), material.shininess) * spotlight.specular;
    }

    float theta = dot(lightDir, normalize(-spotlight.direction));
    float epsilon = spotlight.cutAngle - spotlight.outAngle;
    float intensity = clamp((theta - spotlight.outAngle) / epsilon, 0.0, 1.0);

    contribution += (diffuse + specular) * attenuation * intensity;;

    return contribution;
}

void main(){

    vec3 pointComponents;
    pointComponents = computeDirectionalLightComponents();
    pointComponents = computeSpotlightComponents();
    pointComponents = computePointLightComponents();

    vec3 emissive = texture(material.emissiveMap, coordTexture).rgb;

    outColor = vec4((pointComponents + emissive), 1);
}
