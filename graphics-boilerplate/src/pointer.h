#include "main.h"

#ifndef POINTER_H
#define POINTER_H


class Pointer {
public:
    Pointer() {}
    Pointer(float x, float y, float z, float rot, color_t color);
    glm::vec3 position;
    float rotation;

    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick(float angle);
private:
    VAO *object;
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint colorbuffer;
    GLuint Texture;
    GLuint TextureID;
};

#endif // POINTER_H
