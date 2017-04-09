#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Cube.h"

class Light : public Cube {
    public:
        Light(glm::vec3 color, std::string vertexShader, std::string fragmentShader);
        inline glm::vec3 getPosition() {return _position;}
        inline void setPosition(glm::vec3 position) {_position = position;}
        inline glm::vec3 getColor() {return _lightColor;}
        virtual void load() override;
        virtual void display(glm::mat4 &projection, glm::mat4 &modelView) override;
    private:

        glm::vec3 _position;
        glm::vec3 _lightColor;

        GLuint _lightVAO;
};

#endif // LIGHT_H
