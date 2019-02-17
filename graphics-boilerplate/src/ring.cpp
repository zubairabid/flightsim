#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y, float z, float rot, color_t color) {

    this->position = glm::vec3(x, y, z);
    this->rotation = rot;

    this->omega = 1.0f;
    this->theta = 0.0f;
    this->radius = 10.0f;
    this->dr = 1.0f;


    speed = 1;


    GLfloat vertex_buffer_data[18*360];
    int i = 0;
    while (theta < 360) {
    
        float segment = this->radius * this->omega * M_PI / 180.0f;
        float curr_x = this->radius * sin(this->theta * M_PI / 180.0f);
        float curr_y = this->radius * cos(this->theta * M_PI / 180.0f);
        
        float lb_x = curr_x - segment * cos(this->theta * M_PI /180.0f);
        float lb_y = curr_y - segment * sin(this->theta * M_PI /180.0f);

        float rb_x = curr_x + segment * cos(this->theta * M_PI /180.0f);
        float rb_y = curr_y + segment * sin(this->theta * M_PI /180.0f);

            
        float lt_x = curr_x + this->dr * sin(this->theta * M_PI / 180.0f) - segment * cos(this->theta * M_PI /180.0f);
        float lt_y = curr_y + this->dr * cos(this->theta * M_PI / 180.0f) - segment * sin(this->theta * M_PI /180.0f);
        
        float rt_x = curr_x + this->dr * sin(this->theta * M_PI / 180.0f) + segment * cos(this->theta * M_PI /180.0f);
        float rt_y = curr_y + this->dr * cos(this->theta * M_PI / 180.0f) + segment * sin(this->theta * M_PI /180.0f);
        
        vertex_buffer_data[18*i] = lb_x;
        vertex_buffer_data[18*i+1] = lb_y;
        vertex_buffer_data[18*i+2] = 0;
        
        vertex_buffer_data[18*i+3] = rb_x;
        vertex_buffer_data[18*i+4] = rb_y;
        vertex_buffer_data[18*i+5] = 0;
        
        vertex_buffer_data[18*i+6] = lt_x;
        vertex_buffer_data[18*i+7] = lt_y;
        vertex_buffer_data[18*i+8] = 0;
        
        vertex_buffer_data[18*i+9] = rt_x;
        vertex_buffer_data[18*i+10] = rt_y;
        vertex_buffer_data[18*i+11] = 0;
        
        vertex_buffer_data[18*i+12] = rb_x;
        vertex_buffer_data[18*i+13] = rb_y;
        vertex_buffer_data[18*i+14] = 0;
        
        vertex_buffer_data[18*i+15] = lt_x;
        vertex_buffer_data[18*i+16] = lt_y;
        vertex_buffer_data[18*i+17] = 0;
               

        theta += omega;
        i++;
    }

    GLfloat vertex_colours[sizeof(vertex_buffer_data)*3];
    for (int i = 0; i < sizeof(vertex_buffer_data); i++) {
        vertex_colours[3*i] = 1;
        vertex_colours[3*i+1] = 0.84;
        vertex_colours[3*i+2] = 0;
    }

    this->object = create3DObject(GL_TRIANGLES, sizeof(vertex_buffer_data), vertex_buffer_data, color, GL_FILL);

    glGenBuffers(1, &this->vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_COPY_ARB);

    glGenBuffers(1, &this->colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_colours), vertex_colours, GL_STATIC_DRAW);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of ring arouund which we waant to rotate
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

    glDrawArrays(GL_TRIANGLES, 0, 6*360);



    // draw3DObject(this->object);
}

void Ring::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ring::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

