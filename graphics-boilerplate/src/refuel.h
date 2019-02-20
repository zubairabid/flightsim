#include "main.h"

#ifndef REFUEL_H
#define REFUEL_H


class Refuel {
public:
    Refuel() {}
    Refuel(float x, float y, float z, float rot, color_t color);
    glm::vec3 position;
    float rotation;

    float radius;
    float dr;
    float theta;
    float omega;

    bounding_box_t bounds;

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

#endif // REFUEL_H
