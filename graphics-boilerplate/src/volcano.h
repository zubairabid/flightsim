#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H


class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y, float z, float rot, color_t color);
    glm::vec3 position;
    float rotation;

    bounding_box_t bounds;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object;
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint colorbuffer;
    GLuint Texture;
    GLuint TextureID;
};

#endif // VOLCANO_H
