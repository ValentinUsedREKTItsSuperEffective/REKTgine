#ifndef SCENEOPENGL_H
#define SCENEOPENGL_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Context.hpp"
#include "Input.h"

using namespace glm;

class Scene{
    public:
        Scene(Context* context);
        ~Scene();

        void ExampleOne();
        void ExampleFramework();

    private:
        Context* context;
        Input input;
};

#endif // SCENEOPENGL_H
