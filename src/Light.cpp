#include "Light.h"

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

Light::Light(glm::vec3 color) : lightColor(color) {}
