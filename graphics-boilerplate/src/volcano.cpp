#include "volcano.h"
#include "main.h"

Volcano::Volcano(float x, float y, float z, float rot, color_t color) {

    this->position = glm::vec3(x, y, z);

    this->bounds.x = x;
    this->bounds.y = y;
    this->bounds.z = z;
    this->bounds.radius = 35;
    this->rotation = rot;

    static const GLfloat vertex_buffer_data[] = {
        0.0f, 35.0f, 0.0f,
        25.0f, 0.0f, 25.0f,
        -25.0f, 0.0f, 25.0f,
        0.0f, 35.0f, 0.0f,
        25.0f, 0.0f, 25.0f,
        25.0f, 0.0f, -25.0f,
        0.0f, 35.0f, 0.0f,
        -25.0f, 0.0f, -25.0f,
        -25.0f, 0.0f, 25.0f,
        0.0f, 35.0f, 0.0f,
        -25.0f, 0.0f, -25.0f,
        25.0f, 0.0f, -25.0f        
    };


    static const GLfloat vertex_colours[] = {
        1.0f, 0.0f, 0.0f,
        0.4f, 0.26f, 0.13f,
        0.4f, 0.26f, 0.13f,
        1.0f, 0.0f, 0.0f,
        0.4f, 0.26f, 0.13f,
        0.4f, 0.26f, 0.13f,
        1.0f, 0.0f, 0.0f,
        0.4f, 0.26f, 0.13f,
        0.4f, 0.26f, 0.13f,
        1.0f, 0.0f, 0.0f,
        0.4f, 0.26f, 0.13f,
        0.4f, 0.26f, 0.13f
    };

    this->object = create3DObject(GL_TRIANGLES, sizeof(vertex_buffer_data), vertex_buffer_data, color, GL_FILL);

    glGenBuffers(1, &this->vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_COPY_ARB);

    glGenBuffers(1, &this->colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colours), vertex_colours, GL_STATIC_DRAW);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(10.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 1800.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of volcano arouund which we waant to rotate
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

    glDrawArrays(GL_TRIANGLES, 0, 12);



    // draw3DObject(this->object);
}

void Volcano::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Volcano::tick() {

    this->bounds.x = this->position.x;
    this->bounds.y = this->position.y;
    this->bounds.z = this->position.z;
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

