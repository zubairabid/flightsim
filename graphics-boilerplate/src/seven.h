#include "main.h"

#ifndef SEVEN_H
#define SEVEN_H


class Seven {
public:
    Seven() {}
    Seven(float x, float y, float z, float rot, color_t color);
    glm::vec3 position;
    float rotation;

    float gravity;
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

#endif // SEVEN_H
