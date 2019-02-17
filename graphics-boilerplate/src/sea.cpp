#include "sea.h"
#include "main.h"

Sea::Sea(float x, float y, float z, color_t color) {
    srand (time(NULL));

    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A sea has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -600.0f,-1.0f,-600.0f, // triangle 1 : begin
        -600.0f,-1.0f, 600.0f,
        -600.0f, 1.0f, 600.0f, // triangle 1 : end
        600.0f, 1.0f,-600.0f, // triangle 2 : begin
        -600.0f,-1.0f,-600.0f,
        -600.0f, 1.0f,-600.0f, // triangle 2 : end
        600.0f,-1.0f, 600.0f,
        -600.0f,-1.0f,-600.0f,
        600.0f,-1.0f,-600.0f,
        600.0f, 1.0f,-600.0f,
        600.0f,-1.0f,-600.0f,
        -600.0f,-1.0f,-600.0f,
        -600.0f,-1.0f,-600.0f,
        -600.0f, 1.0f, 600.0f,
        -600.0f, 1.0f,-600.0f,
        600.0f,-1.0f, 600.0f,
        -600.0f,-1.0f, 600.0f,
        -600.0f,-1.0f,-600.0f,
        -600.0f, 1.0f, 600.0f,
        -600.0f,-1.0f, 600.0f,
        600.0f,-1.0f, 600.0f,
        600.0f, 1.0f, 600.0f,
        600.0f,-1.0f,-600.0f,
        600.0f, 1.0f,-600.0f,
        600.0f,-1.0f,-600.0f,
        600.0f, 1.0f, 600.0f,
        600.0f,-1.0f, 600.0f,
        600.0f, 1.0f, 600.0f,
        600.0f, 1.0f,-600.0f,
        -600.0f, 1.0f,-600.0f,
        600.0f, 1.0f, 600.0f,
        -600.0f, 1.0f,-600.0f,
        -600.0f, 1.0f, 600.0f,
        600.0f, 1.0f, 600.0f,
        -600.0f, 1.0f, 600.0f,
        600.0f,-1.0f, 600.0f
    };

    GLfloat vertex_colours[sizeof(vertex_buffer_data)*3];
    for (int i = 0; i < sizeof(vertex_buffer_data); i++) {
        vertex_colours[3*i] = 0.5;
        vertex_colours[3*i+1] = 0.5;
        vertex_colours[3*i+2] = 1;
    }

    this->object = create3DObject(GL_TRIANGLES, sizeof(vertex_buffer_data), vertex_buffer_data, color, GL_FILL);

    glGenBuffers(1, &this->vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_COPY_ARB);

    glGenBuffers(1, &this->colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colours), vertex_colours, GL_STATIC_DRAW);
}

void Sea::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of sea arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, 12*3);



    // draw3DObject(this->object);
}

void Sea::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Sea::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

