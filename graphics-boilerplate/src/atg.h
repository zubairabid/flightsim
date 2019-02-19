#include "main.h"

#ifndef ATG_H
#define ATG_H


class Atg {
public:
    Atg() {}
    Atg(float x, float y, float z, float rot, color_t color);
    glm::vec3 position;
    float rotation;

    float gravity;

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

#endif // ATG_H
