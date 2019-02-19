#include "turret.h"
#include "main.h"
#include "objloader.hpp"
// #include "shader.hpp"  
#include "texture.hpp"
#include "glm/gtx/string_cast.hpp"

extern GLuint programID;

Turret::Turret(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);

    this->bounds.x = x;
    this->bounds.y = y;
    this->bounds.z = z;
    this->bounds.radius = 8;
    this->rotation = 0;
    this->roll = 0;

    this->Texture = loadDDS("../../uvmap.DDS");
    this->TextureID = glGetUniformLocation(programID, "myTextureSampler");

    std::cout << "About to load\n";
    bool res = loadOBJ("../../g1.obj", this->vertices, this->uvs, this->normals);


    // NOT SURE WHY IT IS IMPORTANT BUT DOES NOT RENDER OTHERWISE
    GLfloat vbdata[this->vertices.size()*sizeof(glm::vec3)];
    // GLfloat g_color_buffer_data[this->vertices.size()*sizeof(glm::vec3)*3];
    for (int i = 0; i < this->vertices.size(); i++) {
        vbdata[3*i] = this->vertices[i].x;
        vbdata[3*i+1] = this->vertices[i].y;
        vbdata[3*i+2] = this->vertices[i].z;
        // g_color_buffer_data[9*i] = this->vertices[i].x;
        // g_color_buffer_data[9*i+1] = this->vertices[i].y;
        // g_color_buffer_data[9*i+2] = this->vertices[i].z;
        // g_color_buffer_data[9*i+3] = this->vertices[i].y;
        // g_color_buffer_data[9*i+4] = this->vertices[i].z;
        // g_color_buffer_data[9*i+5] = this->vertices[i].x;
        // g_color_buffer_data[9*i+6] = this->vertices[i].z;
        // g_color_buffer_data[9*i+7] = this->vertices[i].x;
        // g_color_buffer_data[9*i+8] = this->vertices[i].y;
    }
    // std::cout << count << "\t" << this->vertices.size()*3 << std::endl;
    
    std::cout << "Whooooaaaaah we are halfway there\n"; 
    this->object = create3DObject(GL_TRIANGLES, this->vertices.size()*3, vbdata, color, GL_FILL);
    std::cout << "Whooooaaaaah we are living on a prayer\n";



    // GLuint vertexbuffer;
	glGenBuffers(1, &this->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);

	// GLuint uvbuffer;
	glGenBuffers(1, &this->uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);

    // // GLuint colorbuffer;
    // glGenBuffers(1, &this->colorbuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

}

void Turret::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate = rotate * glm::rotate((float) (this->roll*M_PI/180.0f), glm::vec3(0, 0, 1));
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    // // Set our "myTextureSampler" sampler to use Texture Unit 0
    glUniform1i(this->TextureID, 0);

    // 1rst attribute buffer : vertices
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

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
    glVertexAttribPointer(
        1,                                // attribute
        2,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );

    // glEnableVertexAttribArray(1);
    // glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    // glVertexAttribPointer(
    //     1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
    //     3,                                // size
    //     GL_FLOAT,                         // type
    //     GL_FALSE,                         // normalized?
    //     0,                                // stride
    //     (void*)0                          // array buffer offset
    // );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);


    // draw3DObject(this->object);
}

void Turret::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Turret::tick(int forward, int tilt, int up) {

    this->bounds.x = this->position.x;
    this->bounds.y = this->position.y;
    this->bounds.z = this->position.z;
    // std::cout << tilt << std::endl;

    // if (up == -1) {
    //     this->gravity = -0.3;
    // }
    // else if (up == 1) {
    //     this->gravity = 0.3;
    // }
    // else {
    //     this->gravity = 0;
    // }
    // this->position.y += this->gravity;

    // this->position.z += speed*cos(this->rotation*M_PI/180.0f);
    // this->position.x += speed*sin(this->rotation*M_PI/180.0f);

    // if (tilt != 0) {
    //     this->rotation -= tilt;
    //     if (tilt == 1) {
    //         if (this->roll < 25)
    //             this->roll++;
    //     }
    //     else {
    //         if (this->roll > -25)
    //             this->roll--;
    //     }
    // }
    // else {
    //     if (this->roll > 0)
    //         this->roll--;
    //     else if (this->roll < 0)
    //         this->roll++;
    // }

    // // this->rotation += speed;
    // // this->position.x -= speed;
    // // this->position.y -= speed;
    // if (forward == 1) {
    //     if (this->speed < 8)
    //         this->speed += 0.2;
    // }
    // else if (forward == -1) {
    //     if (this->speed > 0)
    //         this->speed -= 0.2;
    // }
    // else {
    //     if (this->speed > 0.4)
    //         this->speed -= 0.2;
    //     else 
    //         this->speed += 0.2;
    // }
}

