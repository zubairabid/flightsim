#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"

#include "common/shader.hpp"
// #include "texture.hpp"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Sea see;

int viewf = 0;
int forward = 0, tilt = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    
    float eye_x = 0, eye_y = 0, eye_z = 0;
    float up_x = 0, up_y = 0, up_z = 0;


    if (viewf == 0) {
        eye_x = ball1.position.x-100*sin(camera_rotation_angle*M_PI/180.0f);
        eye_y = ball1.position.y + 20;
        eye_z = ball1.position.z-100*cos(camera_rotation_angle*M_PI/180.0f);

        up_x = abs(1*sin(camera_rotation_angle*M_PI/180.0f));
        up_y = 1;
        up_z = abs(1*cos(camera_rotation_angle*M_PI/180.0f));

        if ( camera_rotation_angle > 0 && ((((int)camera_rotation_angle % 360) >= 90 && ((int)camera_rotation_angle % 360) < 180) || (((int)camera_rotation_angle % 360) >= 270 && ((int)camera_rotation_angle % 360) < 360))  ) {
            up_z = -up_z;
            // up_x = -up_x;
        }
        if (camera_rotation_angle < 0) {
            up_z = -up_z;
        }
        if (camera_rotation_angle < 0  && ((((int)abs(camera_rotation_angle) % 360) >= 90 && ((int)abs(camera_rotation_angle) % 360) < 180) || (((int)abs(camera_rotation_angle) % 360) >= 270 && ((int)abs(camera_rotation_angle) % 360) < 360))) {
            // up_x = -up_x;
            up_z = -up_z;
        }
    }
    else {
        eye_x = ball1.position.x+80;
        eye_y = ball1.position.y + 20;
        eye_z = ball1.position.z-0;

        up_x = -1;
        up_y = 1;
        up_z = 0;
    }

    cout << "up_x = " << up_x << "\t up_y = " << up_y << "\t up_z = " << up_z << endl;
    cout << "eye_x = " << eye_x << "\t eye_y = " << eye_y << "\t eye_z = " << eye_z << endl;

    glm::vec3 eye (eye_x, eye_y, eye_z);
    // glm::vec3 eye (viewf==0?0:80, viewf==0?20:20, viewf==0?-100:0);
    
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (ball1.position.x, ball1.position.y, ball1.position.z);
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (up_x, up_y, up_z);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    see.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    
    int ahead = glfwGetKey(window, GLFW_KEY_W);
    int behind = glfwGetKey(window, GLFW_KEY_S);
    int tilt_left = glfwGetKey(window, GLFW_KEY_A);
    int tilt_right = glfwGetKey(window, GLFW_KEY_D);
    

    if (left) {
        viewf = 1;
    }
    if (right) {
        viewf = 0;
    }
    
    if (ahead) {
        forward = 1;
    }
    else if (behind) {
        forward = -1;
    }
    else {
        forward = 0;
    }
    
    if (tilt_left) {
        tilt = -1;
    }
    else if (tilt_right) {
        tilt = 1;
    }  
    else {
        tilt = 0;
    }

}

void tick_elements() {
    ball1.tick(forward, tilt);
    camera_rotation_angle = ball1.rotation;
    cout << camera_rotation_angle << endl;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 0, COLOR_GREEN);
    see         = Sea(0, -30, 0, COLOR_GREEN);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 700;
    int height = 700;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(15.0f), 1.0f/1.0f, 0.1f, 500.0f);
}
