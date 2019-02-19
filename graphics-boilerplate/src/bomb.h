#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, float rot, color_t color);
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

#endif // BOMB_H
