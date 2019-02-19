#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float roll;
    float pitch;
    float gravity;
    float limit;

    int points;
    int life;
    int fuel;

    bounding_box_t bounds;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int forward, int tilt, int up, int reverse);
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

#endif // BALL_H
