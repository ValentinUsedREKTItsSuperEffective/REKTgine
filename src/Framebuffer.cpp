#include "Framebuffer.hpp"
#include "Screen.hpp"

Framebuffer::Framebuffer() : geometry(QuadGeometry()), shader(Shader("Shaders/framebuffer.vert", "Shaders/framebuffer.frag")){
    glGenFramebuffers(1, &fbo);
    glGenRenderbuffers(1, &rbo);

    // create a color attachment texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Screen::width, Screen::height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Screen::width, Screen::height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glUseProgram(shader.programID);
    shader.bindInt("screenTexture", GL_TEXTURE0);
}

Framebuffer::~Framebuffer(){
    glDeleteFramebuffers(1, &fbo);
    glDeleteRenderbuffers(1, &rbo);
}

void Framebuffer::Display(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    //glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader.programID);
    geometry.bindVertexArray();
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawElements(GL_TRIANGLES, geometry.indexes.size(), GL_UNSIGNED_SHORT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
    glEnable(GL_DEPTH_TEST);
}

Framebuffer::QuadGeometry::QuadGeometry(){
    positions = {
        -1.f, -1.f,
        1.f, -1.f,
        1.f, 1.f,
        -1.f, 1.f
    };

    uvs = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    indexes = {
        0, 1, 2,
        2, 3, 0
    };

    load();
}

void Framebuffer::QuadGeometry::load(){
    // Geometry
    if(glIsBuffer(vbo) == GL_TRUE){
        glDeleteBuffers(1, &vbo);
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    auto sizeOfPositions = positions.size() * sizeof(float);
    auto sizeOfUvs = uvs.size() * sizeof(float);

    glBufferData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfUvs, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeOfPositions, &positions[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions, sizeOfUvs, &uvs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // EBO
    if(glIsBuffer(ebo) == GL_TRUE){
        glDeleteBuffers(1, &ebo);
    }

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    auto sizeOfIndexes = indexes.size() * sizeof(unsigned short);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndexes, &indexes[0], GL_STATIC_DRAW);

    // VAO
    if(glIsVertexArray(vao) == GL_TRUE)
        glDeleteVertexArrays(1, &vao);

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeOfPositions));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // Don't unbind element buffer before VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Framebuffer::QuadGeometry::~QuadGeometry(){}
