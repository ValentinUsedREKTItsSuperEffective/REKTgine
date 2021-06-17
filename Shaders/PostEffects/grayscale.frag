#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main(){
    vec4 sample = texture(screenTexture, TexCoords);
    float grayscale = sample.r * 0.2126 + sample.g * 0.7152 + sample.b * 0.0722;
    FragColor = vec4(vec3(grayscale), 1.0);
}
