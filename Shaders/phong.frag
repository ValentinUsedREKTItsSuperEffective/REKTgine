#version 330 core

#define MAX_LIGHT 3

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
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    // point light
    float constant;
    float linear;
    float quadratic;

    // spotlight
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
uniform Light lights[MAX_LIGHT];

// Sortie
out vec4 outColor;

vec3 computeLightContribution(vec3 color, Light light){
    vec3 ambient = color * material.ambient * light.ambient;

    vec3 N = normalize(normal);
    vec3 lightDir;

    if(light.constant == 0.0f){ // directional light
        lightDir = normalize(-light.direction);
    } else {
        lightDir = normalize(light.position - position);
    }

    vec3 diffuse = color * max(0.0, dot(lightDir, N)) * light.diffuse;

    vec3 specular = vec3(0.0f);
    if(dot(lightDir, N) >= 0.0f){
        vec3 R = reflect(-lightDir, N);
        vec3 viewDir = normalize(cameraPosition - position);
        specular = material.specular * texture(material.specularMap, coordTexture).rgb * pow(max(0.0, dot(viewDir, R)), material.shininess) * light.specular;
    }

    float attenuation = 1.0;

    if(light.constant > 0){
        float dist = length(light.position - position);
        attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);
    }

    if(light.cutAngle > 0.0f && light.outAngle > 0.0f){ // spotlight only
        float theta = dot(lightDir, normalize(-light.direction));
        float epsilon = light.cutAngle - light.outAngle;
        float intensity = clamp((theta - light.outAngle) / epsilon, 0.0, 1.0);

        diffuse *= intensity;
        specular *= intensity;
    }

    return (ambient + diffuse + specular) * attenuation;
}

void main(){
    vec3 color = material.color * texture(material.map, coordTexture).rgb;

    vec3 pointComponents = vec3(0.0f);
    for(int i = 0; i < MAX_LIGHT; i++){
        pointComponents += computeLightContribution(color, lights[i]);
    }

    vec3 emissive = texture(material.emissiveMap, coordTexture).rgb;

    outColor = vec4((pointComponents + emissive), 1);
}
