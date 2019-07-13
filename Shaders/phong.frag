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

struct PointLight {
    float constant;
    float linear;
    float quadratic;
};

struct Spotlight {
    vec3 direction;
    float cutAngle;
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
    vec3 ambient = color * material.ambient * light.ambient;

    vec3 N = normalize(normal);
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

vec3 computePointLightComponents(){
    float dist = length(light.position - position);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * dist * dist);

    vec3 color = material.color * texture(material.map, coordTexture).rgb;
    vec3 ambient = color * material.ambient * light.ambient;

    vec3 N = normalize(normal);
    vec3 lightDir = normalize(light.position - position);
    vec3 diffuse = color * max(0.0, dot(lightDir, N)) * light.diffuse;

    vec3 specular = vec3(0.0f);
    if(dot(lightDir, N) >= 0.0f){
        vec3 R = reflect(-lightDir, N);
        vec3 viewDir = normalize(cameraPosition - position);
        specular = material.specular * texture(material.specularMap, coordTexture).rgb * pow(max(0.0, dot(viewDir, R)), material.shininess) * light.specular;
    }

    return (ambient + diffuse + specular) * attenuation;
}

vec3 computeSpotlightComponents(){
    vec3 nonNormalizedLightDir = light.position - position;
    vec3 lightDir = normalize(nonNormalizedLightDir);

    float dist = length(nonNormalizedLightDir);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * dist * dist);

    vec3 color = material.color * texture(material.map, coordTexture).rgb;
    vec3 ambient = color * material.ambient * light.ambient;

    vec3 contribution = ambient * attenuation;

    float theta = dot(lightDir, normalize(spotlight.direction));

    if(theta > spotlight.cutAngle){
        vec3 N = normalize(normal);
        vec3 diffuse = color * max(0.0, dot(lightDir, N)) * light.diffuse;

        vec3 specular = vec3(0.0f);
        if(dot(lightDir, N) >= 0.0f){
            vec3 R = reflect(-lightDir, N);
            vec3 viewDir = normalize(cameraPosition - position);
            specular = material.specular * texture(material.specularMap, coordTexture).rgb * pow(max(0.0, dot(viewDir, R)), material.shininess) * light.specular;
        }

        contribution += (diffuse + specular) * attenuation;
    }

    return contribution;
}

void main(){

    vec3 pointComponents = computeSpotlightComponents();

    vec3 emissive = texture(material.emissiveMap, coordTexture).rgb;

    outColor = vec4((pointComponents + emissive), 1);
}
