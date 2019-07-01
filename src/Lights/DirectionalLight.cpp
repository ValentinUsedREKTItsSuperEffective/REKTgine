#include "Lights/DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 col, glm::vec3 amb, glm::vec3 dif, glm::vec3 spec) : Light(col, amb, dif, spec){}

DirectionalLight::~DirectionalLight(){}
