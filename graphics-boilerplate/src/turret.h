#include "main.h"

#ifndef TURRET_H
#define TURRET_H


class Turret {
public:
    Turret() {}
    Turret(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float roll;
    float gravity;
    float limit;

    bounding_box_t bounds;
    bounding_box_t distance;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int forward, int tilt, int up);
    double speed;
private:
    VAO *object;
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint colorbuffer;
    GLuint Texture;
    GLuint TextureID;
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;
};

#endif // TURRET_H
