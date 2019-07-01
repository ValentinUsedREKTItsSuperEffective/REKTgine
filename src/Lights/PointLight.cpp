#include "Lights/PointLight.h"

PointLight::PointLight(glm::vec3 col, glm::vec3 amb, glm::vec3 dif, glm::vec3 spec) : Light(col, amb, dif, spec){}

PointLight::~PointLight(){}
