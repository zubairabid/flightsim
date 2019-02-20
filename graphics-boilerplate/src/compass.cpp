#include "compass.h"
#include "main.h"

Compass::Compass(float x, float y, float z, float rot, color_t color) {

    this->position = glm::vec3(x, y, z);
    this->rotation = rot;

    static const GLfloat vertex_buffer_data[] = {
        -0.1f, 0.0f, 0.0f,
        0.1f, 0.0f, 0.0f,
        0.0f, 0.6f, 0.0f,
        -0.1f, 0.0f, 0.0f,
        0.1f, 0.0f, 0.0f,
        0.0f, -0.6f, 0.0f
    };


    static const GLfloat vertex_colours[] = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    this->object = create3DObject(GL_TRIANGLES, sizeof(vertex_buffer_data), vertex_buffer_data, color, GL_FILL);

    glGenBuffers(1, &this->vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_COPY_ARB);

    glGenBuffers(1, &this->colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colours), vertex_colours, GL_STATIC_DRAW);
}

void Compass::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(10.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // std::cout << "Rotation: " << this->rotation << std::endl;
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // rotate  *= glm::rotate((float)(10* M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of compass arouund which we waant to rotate
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

    glDrawArrays(GL_TRIANGLES, 0, 6);



    // draw3DObject(this->object);
}

void Compass::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Compass::tick(float angle) {
    this->rotation = angle;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

