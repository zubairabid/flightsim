#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z, float rot, color_t color);
    glm::vec3 position;
    float rotation;

    float radius;
    float dr;
    float theta;
    float omega;

    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint colorbuffer;
    GLuint Texture;
    GLuint TextureID;
};

#endif // RING_H
