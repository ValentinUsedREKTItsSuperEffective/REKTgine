#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <GL/glew.h>

#include <vector>

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

using namespace std;

class Geometry {
    public:
        vector<float> positions;
        vector<float> normals;
        vector<float> uvs;
        vector<unsigned short> indexes;

        Geometry();
        virtual ~Geometry();
        virtual void load();
        void bindVertexArray();

    protected:
        GLuint vbo;
        GLuint vao;
        GLuint ebo;
};

#endif // GEOMETRY_H
