#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:
    Compass() {}
    Compass(float x, float y, float z, float rot, color_t color);
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

#endif // COMPASS_H
