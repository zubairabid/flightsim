#include "seven.h"
#include "main.h"

Seven::Seven(float x, float y, float z, float rot, color_t color) {

    this->position = glm::vec3(x, y, z);
    this->rotation = rot;


    GLfloat a[] = { // DONE
        -0.11f, 0.11f, 0.0f,
        -0.08f, 0.08f, 0.0f,
        0.11f, 0.11f, 0.0f,
        -0.08f, 0.08f, 0.0f,
        0.11f, 0.11f, 0.0f,
        0.08f, 0.08f, 0.0f
    };

    GLfloat b[] = {
        -0.11f, 0.11f, 0.0f,
        -0.08f, 0.08f, 0.0f,
        -0.08f, 0.02f, 0.0f,
        -0.11f, 0.11f, 0.0f,
        -0.08f, 0.08f, 0.0f,
        -0.11f, 0.02f, 0.0f
    };

    GLfloat c[] = {
        -0.11f, -0.11f, 0.0f,
        -0.08f, -0.08f, 0.0f,
        -0.08f, -0.02f, 0.0f,
        -0.11f, -0.11f, 0.0f,
        -0.08f, -0.08f, 0.0f,
        -0.11f, -0.02f, 0.0f
    };

    GLfloat d[] = {
        -0.11f, -0.11f, 0.0f,
        -0.08f, -0.08f, 0.0f,
        0.11f, -0.11f, 0.0f,
        -0.08f, -0.08f, 0.0f,
        0.11f, -0.11f, 0.0f,
        0.08f, -0.08f, 0.0f
    };

    GLfloat e[] = {
        0.11f, -0.11f, 0.0f,
        0.08f, -0.08f, 0.0f,
        0.08f, -0.02f, 0.0f,
        0.11f, -0.11f, 0.0f,
        0.08f, -0.08f, 0.0f,
        0.11f, -0.02f, 0.0f
    };

    GLfloat f[] = {
        0.11f, 0.11f, 0.0f,
        0.08f, 0.08f, 0.0f,
        0.08f, 0.02f, 0.0f,
        0.11f, 0.11f, 0.0f,
        0.08f, 0.08f, 0.0f,
        0.11f, 0.02f, 0.0f
    };

    GLfloat g[] = {
        -0.08f, 0.02f, 0.0f,
        -0.08f, -0.02f, 0.0f,
        0.08f, 0.02f, 0.0f,
        -0.08f, -0.02f, 0.0f,
        0.08f, 0.02f, 0.0f,
        0.08f, -0.02f, 0.0f
    };
    
    // GLfloat a_colours[sizeof(a)*3];
    // GLfloat b_colours[sizeof(b)*3];
    // GLfloat c_colours[sizeof(c)*3];
    // GLfloat d_colours[sizeof(d)*3];
    // GLfloat e_colours[sizeof(e)*3];
    // GLfloat f_colours[sizeof(f)*3];
    // GLfloat g_colours[sizeof(g)*3];
    
    // for (int i = 0; i < sizeof(a_colours); i++) {
    //     a_colours[3*i] = 0.8;
    //     a_colours[3*i+1] = 0;
    //     a_colours[3*i+2] = 0;

    //     d_colours[3*i] = 0.8;
    //     d_colours[3*i+1] = 0;
    //     d_colours[3*i+2] = 0;

    //     g_colours[3*i] = 0.8;
    //     g_colours[3*i+1] = 0;
    //     g_colours[3*i+2] = 0;
    // }
    std::cout << "Yeh toh hona hi tha" << std::endl;

    // for (int i = 0; i < sizeof(b_colours); i++) {
    //     b_colours[3*i] = 0.8;
    //     b_colours[3*i+1] = 0;
    //     b_colours[3*i+2] = 0;

    //     c_colours[3*i] = 0.8;
    //     c_colours[3*i+1] = 0;
    //     c_colours[3*i+2] = 0;

    //     e_colours[3*i] = 0.8;
    //     e_colours[3*i+1] = 0;
    //     e_colours[3*i+2] = 0;
    
    //     f_colours[3*i] = 0.8;
    //     f_colours[3*i+1] = 0;
    //     f_colours[3*i+2] = 0;
    // }
    std::cout << "Printed" << std::endl;
    

    this->a_obj = create3DObject(GL_TRIANGLES, sizeof(a), a, color, GL_FILL);

    glGenBuffers(1, &this->a_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->a_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(a), a, GL_STATIC_COPY_ARB);

    // glGenBuffers(1, &this->a_cbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, this->a_cbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(a_colours), a_colours, GL_STATIC_DRAW);


    this->b_obj = create3DObject(GL_TRIANGLES, sizeof(b), b, color, GL_FILL);

    glGenBuffers(1, &this->b_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->b_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(b), b, GL_STATIC_COPY_ARB);

    // glGenBuffers(1, &this->b_cbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, this->b_cbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(b_colours), b_colours, GL_STATIC_DRAW);


    this->c_obj = create3DObject(GL_TRIANGLES, sizeof(c), c, color, GL_FILL);

    glGenBuffers(1, &this->c_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->c_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(c), c, GL_STATIC_COPY_ARB);

    // glGenBuffers(1, &this->c_cbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, this->c_cbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(c_colours), c_colours, GL_STATIC_DRAW);


    this->d_obj = create3DObject(GL_TRIANGLES, sizeof(d), d, color, GL_FILL);

    glGenBuffers(1, &this->d_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->d_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(d), d, GL_STATIC_COPY_ARB);

    // glGenBuffers(1, &this->d_cbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, this->d_cbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(d_colours), d_colours, GL_STATIC_DRAW);


    this->e_obj = create3DObject(GL_TRIANGLES, sizeof(e), e, color, GL_FILL);

    glGenBuffers(1, &this->e_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->e_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(e), e, GL_STATIC_COPY_ARB);

    // glGenBuffers(1, &this->e_cbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, this->e_cbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(e_colours), e_colours, GL_STATIC_DRAW);


    this->f_obj = create3DObject(GL_TRIANGLES, sizeof(f), f, color, GL_FILL);

    glGenBuffers(1, &this->f_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->f_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(f), f, GL_STATIC_COPY_ARB);

    // glGenBuffers(1, &this->f_cbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, this->f_cbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(f_colours), f_colours, GL_STATIC_DRAW);


    this->g_obj = create3DObject(GL_TRIANGLES, sizeof(g), g, color, GL_FILL);

    glGenBuffers(1, &this->g_vbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->g_vbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g), g, GL_STATIC_COPY_ARB);

    // glGenBuffers(1, &this->g_cbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, this->g_cbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(g_colours), g_colours, GL_STATIC_DRAW);
    std::cout << "This should be printed" << std::endl;
}

void Seven::draw(glm::mat4 VP, int light) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of seven arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);


    if (light == 0) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->a_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 1) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->b_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 2) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->c_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 3) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->d_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 4) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->e_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 5) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->f_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    if (light == 6) {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->g_vbuffer);
        glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    // glEnableVertexAttribArray(1);
    // glBindBuffer(GL_ARRAY_BUFFER, a_cbuffer);
    // glVertexAttribPointer(
    //     1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
    //     3,                                // size
    //     GL_FLOAT,                         // type
    //     GL_FALSE,                         // normalized?
    //     0,                                // stride
    //     (void*)0                          // array buffer offset
    // );


    // draw3DObject(this->object);
}

void Seven::draw_num(glm::mat4 VP, int digit) {
    switch (digit)
    {
        case 0:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 2);
            this->draw(VP, 3);
            this->draw(VP, 4);
            this->draw(VP, 5);
            break;
    
        case 1:
            this->draw(VP, 1);
            this->draw(VP, 2);
            break;
    
        case 2:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 3);
            this->draw(VP, 4);
            this->draw(VP, 6);
            break;
    
        case 3:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 2);
            this->draw(VP, 3);
            this->draw(VP, 6);
            break;
    
        case 4:
            this->draw(VP, 1);
            this->draw(VP, 2);
            this->draw(VP, 5);
            this->draw(VP, 6);
            break;
    
        case 5:
            this->draw(VP, 0);
            this->draw(VP, 5);
            this->draw(VP, 6);
            this->draw(VP, 2);
            this->draw(VP, 3);
            break;
    
        case 6:
            this->draw(VP, 0);
            this->draw(VP, 5);
            this->draw(VP, 6);
            this->draw(VP, 4);
            this->draw(VP, 2);
            this->draw(VP, 3);
            break;
    
        case 7:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 2);
            break;
    
        case 8:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 2);
            this->draw(VP, 3);
            this->draw(VP, 4);
            this->draw(VP, 5);
            this->draw(VP, 6);
            break;
    
        case 9:
            this->draw(VP, 0);
            this->draw(VP, 1);
            this->draw(VP, 2);
            this->draw(VP, 3);
            this->draw(VP, 5);
            this->draw(VP, 6);
            break;
    
            
        default:
            break;
    }
}

void Seven::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Seven::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
    // this->position.y -= this->gravity;

    // this->bounds.x = this->position.x;
    // this->bounds.y = this->position.y;
    // this->bounds.z = this->position.z;
}

