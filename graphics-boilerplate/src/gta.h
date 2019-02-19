#include "main.h"

#ifndef GTA_H
#define GTA_H


class Gta {
public:
    Gta() {}
    Gta(float x, float y, float z, float rot, color_t color);
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

#endif // GTA_H
