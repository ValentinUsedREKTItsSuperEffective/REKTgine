#ifndef SCENEOPENGL_H
#define SCENEOPENGL_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Context.hpp"
#include "Input.h"
#include "Lights/Light.h"
#include "Mesh.hpp"

using namespace glm;

class Scene{
    public:
        Scene(Context* context);
        ~Scene();

        void Add(Mesh*);

        void ExampleOne();
        void ExampleFramework();

    private:
        Context* context;
        Input input;

        std::vector<Light*> lights;
};

#endif // SCENEOPENGL_H
