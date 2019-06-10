#include "Lights/Light.h"

Light::Light(glm::vec3 color, float intensity = 1.f) : Object3D(), lightColor(color), intensity(intensity) {}
