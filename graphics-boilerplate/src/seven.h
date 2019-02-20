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

    void draw(glm::mat4 VP, int light);
    void draw_num(glm::mat4 VP, int digit);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *a_obj;
    GLuint a_vbuffer;
    GLuint a_uvbuffer;
    GLuint a_cbuffer;
    
    VAO *b_obj;
    GLuint b_vbuffer;
    GLuint b_uvbuffer;
    GLuint b_cbuffer;
    
    VAO *c_obj;
    GLuint c_vbuffer;
    GLuint c_uvbuffer;
    GLuint c_cbuffer;
    
    VAO *d_obj;
    GLuint d_vbuffer;
    GLuint d_uvbuffer;
    GLuint d_cbuffer;
    
    VAO *e_obj;
    GLuint e_vbuffer;
    GLuint e_uvbuffer;
    GLuint e_cbuffer;
    
    VAO *f_obj;
    GLuint f_vbuffer;
    GLuint f_uvbuffer;
    GLuint f_cbuffer;
    
    VAO *g_obj;
    GLuint g_vbuffer;
    GLuint g_uvbuffer;
    GLuint g_cbuffer;
};

#endif // SEVEN_H
