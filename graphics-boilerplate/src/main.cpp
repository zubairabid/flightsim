#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"
#include "line.h"
#include "ring.h"
#include "volcano.h"
#include "pointer.h"
#include "turret.h"
#include "atg.h"
#include "gta.h"
#include "bomb.h"
#include "refuel.h"
#include "compass.h"
#include "parachute.h"

#include "seven.h"

#include "common/shader.hpp"
// #include "texture.hpp"

using namespace std;

GLMatrices Matrices;
GLMatrices test;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

const int SEA_LEVEL = -60;
const int PERSCAM_DIST = 200;
const int C_VOL = 30;
const int C_RING = 100;
const int C_TURR = 50;
const int C_ATG = 300;
const int C_BOMB = 100;
const int C_GTA = 300;
const int C_PAR = 300;
int count_gta = 0;
int count_atg = 0;
int count_bomb = 0;
int current_bullet = 0;
int current_bomb = 0;
int current_homing = 0;
const int LIM = 1300;


Ball ball1;
Sea see;
Line line;
Refuel pump;
Compass compass;

Seven life[3];
Seven points[3];
Seven fuel[3];


Ring rings[C_RING];
int ring_clear[C_RING];
Volcano volcanoes[C_VOL];
Turret turrets[C_TURR];
int turret_clear[C_TURR];
Atg bullets[C_ATG];
Gta homing[C_GTA];
Bomb bombs[C_BOMB];
Parachute chutes[C_PAR];
int chute_clear[C_PAR];

Pointer arrow;


float fov = 700.0f;
int viewf = 1;
int current = 0;
int forward = 0, tilt = 0, up = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float heli_rotation_x = 0;
float heli_rotation_y = 0;



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
    float look_x = ball1.position.x, look_y = ball1.position.y, look_z = ball1.position.z;

    // cout << "VIEWF: " << viewf << endl;
    if (viewf == 1) {
        // cout << "perspective view";
        eye_x = ball1.position.x-PERSCAM_DIST*sin(camera_rotation_angle*M_PI/180.0f);
        eye_y = ball1.position.y + 20;
        eye_z = ball1.position.z-PERSCAM_DIST*cos(camera_rotation_angle*M_PI/180.0f);

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
    else if (viewf == 2) { // Plane view
        // cout << "plane view";

        look_x = ball1.position.x+20*sin(camera_rotation_angle*M_PI/180.0f);
        look_y = ball1.position.y-0.5;
        look_z = ball1.position.z+20*cos(camera_rotation_angle*M_PI/180.0f);

        eye_x = ball1.position.x+15*sin(camera_rotation_angle*M_PI/180.0f);
        eye_y = ball1.position.y;
        eye_z = ball1.position.z+15*cos(camera_rotation_angle*M_PI/180.0f);

        up_x = abs(1*sin(camera_rotation_angle*M_PI/180.0f));
        up_y = 0.2;
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
    else if (viewf == 3) { // Top view

        eye_x = ball1.position.x;
        eye_y = ball1.position.y+ 500;
        eye_z = ball1.position.z;

        // up_x = -1*sin(camera_rotation_angle*M_PI/180.0f);
        // up_y = 1*cos(camera_rotation_angle*M_PI/180.0f);
        up_x = 1;
        up_y = 1;
        up_z = 1;

        // if ( camera_rotation_angle > 0 && ((((int)camera_rotation_angle % 360) >= 90 && ((int)camera_rotation_angle % 360) < 180) || (((int)camera_rotation_angle % 360) >= 270 && ((int)camera_rotation_angle % 360) < 360))  ) {
        //     up_z = -up_z;
        //     // up_x = -up_x;
        // }
        // if (camera_rotation_angle < 0) {
        //     up_z = -up_z;
        // }
        // if (camera_rotation_angle < 0  && ((((int)abs(camera_rotation_angle) % 360) >= 90 && ((int)abs(camera_rotation_angle) % 360) < 180) || (((int)abs(camera_rotation_angle) % 360) >= 270 && ((int)abs(camera_rotation_angle) % 360) < 360))) {
        //     // up_x = -up_x;
        //     up_z = -up_z;
        // }
    }
    else if (viewf == 4) {
        eye_x = 0;
        eye_y = 0;
        eye_z = 0;

        look_x = ball1.position.x;
        look_y = ball1.position.y;
        look_z = ball1.position.z;
        
        up_x = 0;
        up_y = 1;
        up_z = 0;
        
        fov = 1400.0f; 
    }
    else if (viewf == 5) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        eye_x = ball1.position.x-PERSCAM_DIST*sin(heli_rotation_x*M_PI/180.0f)*cos(heli_rotation_y*M_PI/180.0f);
        eye_y = ball1.position.y + 55*sin(heli_rotation_y*M_PI/180.0f);
        eye_z = ball1.position.z-PERSCAM_DIST*cos(heli_rotation_x*M_PI/180.0f)*cos(heli_rotation_y*M_PI/180.0f);

        up_x = 0;
        up_y = 1;
        up_z = 0;

        look_x = ball1.position.x;
        look_y = ball1.position.y;
        look_z = ball1.position.z;

        double x, y;
        glfwGetCursorPos(window, &x, &y);
        glfwSetCursorPos(window, 350, 350);

        heli_rotation_x += (x - 350);
        heli_rotation_y += (y - 350);

        // cout << "X: " << x << "\tY: " << y << endl;
    }
    // if {
    //     eye_x = ball1.position.x+80;
    //     eye_y = ball1.position.y + 20;
    //     eye_z = ball1.position.z-0;

    //     up_x = -1;
    //     up_y = 1;
    //     up_z = 0;
    // }

    // cout << "up_x = " << up_x << "\t up_y = " << up_y << "\t up_z = " << up_z << endl;
    // cout << "eye_x = " << eye_x << "\t eye_y = " << eye_y << "\t eye_z = " << eye_z << endl;

    glm::vec3 eye (eye_x, eye_y, eye_z);
    // glm::vec3 eye (viewf==0?0:80, viewf==0?20:20, viewf==0?-100:0);
    
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (look_x, look_y, look_z);
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (up_x, up_y, up_z);


    glm::vec3 st_eye (0, 0, -10);
    glm::vec3 st_target (0, 0, 0);
    glm::vec3 st_up (0, 1, 0);



    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    test.view = glm::lookAt(st_eye, st_target, st_up);
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 st_VP = test.projection * test.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Dash render
    int lifepercentage = (int)(ball1.life/20.0);
    life[0].draw_num(st_VP, lifepercentage%10);
    life[1].draw_num(st_VP, (lifepercentage/10)%10);
    life[2].draw_num(st_VP, (lifepercentage)/100);
    
    int score = ball1.points;
    points[0].draw_num(st_VP, score%10);
    points[1].draw_num(st_VP, (score/10)%10);
    points[2].draw_num(st_VP, (score/100));

    int fuelamount = ball1.fuel/100;
    fuel[0].draw_num(st_VP, fuelamount%10);
    fuel[1].draw_num(st_VP, (fuelamount/10)%10);
    fuel[2].draw_num(st_VP, (fuelamount/100));

    compass.draw(st_VP);


    // Scene render
    ball1.draw(VP);
    arrow.draw(VP);
    see.draw(VP);
    line.draw(VP);
    pump.draw(VP);
    
    for (int i = 0; i < C_TURR; i++) {
        if (turret_clear[i] == 0)
            turrets[i].draw(VP);
    }
    for (int i = 0; i < C_RING; i++) {
        if(ring_clear[i] == 0)
            rings[i].draw(VP);
    }
    for (int i = 0; i < count_atg; i++) {
        bullets[i].draw(VP);
    }
    for (int i = 0; i < count_gta; i++) {
        // cout << "Drawing homing";
        homing[i].draw(VP);
    }
    for (int i = 0; i < count_bomb; i++) {
        bombs[i].draw(VP);
    }
    for (int i = 0; i < C_VOL; i++) {
        volcanoes[i].draw(VP);
    }
    for (int i = 0; i < C_PAR; i++) {
        if (chute_clear[i] == 0)
            chutes[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int one  = glfwGetKey(window, GLFW_KEY_1);
    int two = glfwGetKey(window, GLFW_KEY_2);
    int three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4);
    int five = glfwGetKey(window, GLFW_KEY_5);
    
    int ahead = glfwGetKey(window, GLFW_KEY_W);
    int behind = glfwGetKey(window, GLFW_KEY_S);
    int tilt_left = glfwGetKey(window, GLFW_KEY_A);
    int tilt_right = glfwGetKey(window, GLFW_KEY_D);

    int move_up = glfwGetKey(window, GLFW_KEY_UP);
    int move_down = glfwGetKey(window, GLFW_KEY_DOWN);

    int click1 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int click2 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    // int click1 = glfwGetKey(window, GLFW_KEY_RIGHT);
    // int click2 = glfwGetKey(window, GLFW_KEY_LEFT);
    
    if (click1) {
        create_atg();
    }
    if (click2) {
        create_bomb();
    }



    if (one) {
        viewf = 1;
    }
    if (two) {
        viewf = 2;
    }
    if (three) {
        viewf = 3;
    }
    if (four) {
        viewf = 4;
    }
    if (five) {
        viewf = 5;
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

    if (move_up) {
        up = 1;
    }
    else if (move_down) {
        up = -1;
    }
    else {
        up = 0;
    }

}

void create_atg() {
    if (count_atg < C_ATG) {
        count_atg++;
    }
    float x, y, z;
    x = ball1.position.x+10*sin(camera_rotation_angle*M_PI/180.0f);
    y = ball1.position.y;
    z = ball1.position.z+10*cos(camera_rotation_angle*M_PI/180.0f);

    bullets[current_bullet] = Atg(x, y, z, camera_rotation_angle, COLOR_BLACK);
    current_bullet = (current_bullet+1)%C_ATG;
}
void create_gta(int i) {
    if (count_gta < C_GTA) {
        count_gta++;
    }
    float x, y, z;
    x = turrets[i].position.x;
    y = turrets[i].position.y+10;
    z = turrets[i].position.z;

    float angle = atan( ( ball1.position.x - x ) / ( ball1.position.z - z ) ) * 180.0 / M_PI;
    // cout << "Angle of GTA: " << angle << endl;

    if (ball1.position.z <= z)
        homing[current_homing] = Gta(x, y, z, -angle, COLOR_BLACK);
    else
        homing[current_homing] = Gta(x, y, z, 180-angle, COLOR_BLACK);;
    current_homing = (current_homing+1)%C_GTA;
}
void create_bomb() {
    if (count_bomb < C_BOMB) {
        count_bomb++;
    }
    float x, y, z;
    x = ball1.position.x;
    y = ball1.position.y-3;
    z = ball1.position.z;

    bombs[current_bomb] = Bomb(x, y, z, camera_rotation_angle, COLOR_BLACK);
    current_bomb = (current_bomb+1)%C_BOMB;
}

void tick_elements() {
    bool reverse_plane = false, coll_ring = false, dead = false;
    // 
    // 
    // 
    // 
    // COLLISIONS
    // 
    // 
    // 
    // 

    // PLANE VS SURROUNDINGS
    if (ball1.position.x >= LIM || ball1.position.z >= LIM || ball1.position.x <= -LIM || ball1.position.z <= -LIM) {
        reverse_plane = true;
        ball1.fuel -= 1000;
    }

    // PLANE VS SEA
    if (ball1.position.y <= SEA_LEVEL) {
        dead = true;
    }

    // PLANE VS THE REALITY OF LIFE
    if (ball1.life <= 0)
        dead = true;

    // PLANE VS LIL PUMP
    if (detect_collision(ball1.bounds, pump.bounds)) {
        float x = rand() % (LIM/5);
        float z = rand() % (LIM/5);
        ball1.fuel+=5000;
        pump = Refuel(x, SEA_LEVEL/2.0, z, 0, COLOR_GREEN);
    }

    // VOLCANO V PLANE
    for (int i = 0; i < C_VOL; i++) {
        if (detect_collision_lite(volcanoes[i].bounds, ball1.bounds)) {
            // cout << "Collided with a volcano" << endl;
            ball1.life--;
            dead = true;
        }
    }

    // PLANE V RING
    for (int i = 0; i < C_RING; i++) {
        if (ring_clear[i] == 0 && detect_collision_lite(ball1.bounds, rings[i].bounds)) {
            ring_clear[i] = 1;
            ball1.points+=20;
        }
    }

    // BULLET V CANNON
    for (int i = 0; i < count_atg; i++) {
        for (int j = 0; j < C_TURR; j++) {
            if (turret_clear[j] == 0 && detect_collision(bullets[i].bounds, turrets[j].bounds)) {
                // cout << "DELETE THIS CANNON" << endl;
                turret_clear[j] = 1;
                if (j == current) {
                    ball1.points += 100;
                }
            }
        }
    }

    // BOMB VS CANNON
    for (int i = 0; i < count_bomb; i++) {
        for (int j = 0; j < C_BOMB; j++) {
            if (turret_clear[j] == 0 && detect_collision(bombs[i].bounds, turrets[j].bounds)) {
                // cout << "DELETE THIS CANNON" << endl;
                turret_clear[j] = 1;
                if (j == current) {
                    ball1.points += 100;
                }
            }
        }
    }

    // CANNON VS PLANE
    for (int i = 0; i < C_TURR; i++) {
        if (turret_clear[i] == 0 && detect_collision(turrets[i].distance, ball1.bounds)) {
            // cout << "launching bullets from " << i << endl;
            create_gta(i);
        }
    }

    // HOMING VS PLANE
    for (int i = 0; i < count_gta; i++) {
        if (detect_collision(homing[i].bounds, ball1.bounds)) {
            ball1.life -= 1;
        }
    }

    // PARACHUTE VS PLANE
    for (int i = 0; i < C_PAR; i++) {
        if (chute_clear[i] == 0 && detect_collision(chutes[i].distance, ball1.bounds)) {
            chutes[i].tick();
        }
    }

    // BULLET VS PARACHUTE
    for (int i = 0; i < C_PAR; i++) {
        for(int j = 0; j < count_atg; j++) {
            if (chute_clear[i] == 0 && detect_collision(bullets[j].bounds, chutes[i].bounds)) {
                chute_clear[i] = 1;
                ball1.points += 10;
            }
        }
    }

    // BOMB VS PARACHUTE
    for (int i = 0; i < C_PAR; i++) {
        for(int j = 0; j < count_bomb; j++) {
            if (chute_clear[i] == 0 && detect_collision(bombs[j].bounds, chutes[i].bounds)) {
                chute_clear[i] = 1;
            }
        }
    }

    
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 
    // 


    if (dead)
        return;

    while (turret_clear[current] == 1) {
        current++;
    }


    // cout << "Life: " << ball1.life << "\tPoints: " << ball1.points << "\tFuel: " << ball1.fuel << endl;
    float angle = atan( ( turrets[current].position.x - ball1.position.x ) / ( turrets[current].position.z - ball1.position.z ) ) * 180.0f / M_PI;
    if (ball1.position.z > turrets[current].position.z)
        angle += 180;
    // cout << "Angle: " << angle << endl;
    
    if (reverse_plane) {
        ball1.tick(0, 0, up, 1);
    }
    else {
        ball1.tick(forward, tilt, up, 0);
    }
    
    arrow.tick(angle);

    camera_rotation_angle = ball1.rotation;
    see.set_position(ball1.position.x, SEA_LEVEL, ball1.position.z);
    arrow.set_position(ball1.position.x, ball1.position.y+20, ball1.position.z);
    compass.rotation = camera_rotation_angle;

    for (int i = 0; i < count_atg; i++) {
        bullets[i].tick();
    }
    for (int i = 0; i < count_gta; i++) {
        homing[i].tick();
    }
    for (int i = 0; i < count_bomb; i++) {
        bombs[i].tick();
    }

    // cout << "x: " << ball1.position.x << "\ty: " << ball1.position.y << "\tz: " << ball1.position.z << "\trot: " << camera_rotation_angle << endl;
    // cout << camera_rotation_angle << endl;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(0, 0, COLOR_GREEN);
    
    gen_dash();
    gen_map();
    
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

void gen_dash() {
    life[2] = Seven(-2, -3.5, 0, 0, COLOR_BLACK);
    life[1] = Seven(-2.5, -3.5, 0, 0, COLOR_BLACK);
    life[0] = Seven(-3, -3.5, 0, 0, COLOR_BLACK);
    
    points[2] = Seven(-2, -3, 0, 0, COLOR_BLACK);
    points[1] = Seven(-2.5, -3, 0, 0, COLOR_BLACK);
    points[0] = Seven(-3, -3, 0, 0, COLOR_BLACK);

    fuel[2] = Seven(-2, -2.5, 0, 0, COLOR_BLACK);
    fuel[1] = Seven(-2.5, -2.5, 0, 0, COLOR_BLACK);
    fuel[0] = Seven(-3, -2.5, 0, 0, COLOR_BLACK);

    compass = Compass(2.5, -3, 0, camera_rotation_angle, COLOR_BLACK);
}

void gen_map() {
    srand(time(NULL));
    // Sea generation
    see         = Sea(0, SEA_LEVEL, 0, COLOR_GREEN);
    line = Line(0, SEA_LEVEL, 0, COLOR_BLACK);

    // Getting the pointer
    arrow = Pointer(ball1.position.x, ball1.position.y+20, ball1.position.z, 0, COLOR_BLACK);

    float x, z;
    // Ring gen
    for (int i = 0; i < C_RING; i++) {
        x = (rand() % (2*LIM)) - LIM;
        z = (rand() % (2*LIM)) - LIM;
        rings[i] = Ring(x, 0, z, 10*i, COLOR_BLACK);
        ring_clear[i] = 0;
        cout << "Ring generated at " << x << ", " << z << endl;
    }

    // Volcano gen
    for (int i = 0; i < C_VOL; i++) {
        x = (rand() % (2*LIM)) - LIM;
        z = (rand() % (2*LIM)) - LIM;
        volcanoes[i] = Volcano(x, SEA_LEVEL, z, 0, COLOR_BLACK);
        cout << "Volcano generated at " << x << ", " << z << endl;
    }

    // Turret gen
    for (int i = 0; i < C_VOL; i++) {
        x = (rand() % (2*LIM)) - LIM;
        z = (rand() % (2*LIM)) - LIM;
        turrets[i] = Turret(x, SEA_LEVEL, z, COLOR_BLACK);
        turret_clear[i] = 0;
        cout << "Turret generated at " << x << ", " << z << endl;
        // turrets[0] = Turret(0, SEA_LEVEL, 0, COLOR_BLACK);
        // turret_clear[0] = 0;
    }
    
    // Chute gen
    for (int i = 0; i < C_VOL; i++) {
        x = (rand() % (2*LIM)) - LIM;
        z = (rand() % (2*LIM)) - LIM;
        chutes[i] = Parachute(x, 20, z, COLOR_BLACK);
        chute_clear[i] = 0;
        cout << "Chute generated at " << x << ", " << z << endl;
    }

    x = rand() % (LIM/5);
    z = rand() % (LIM/5);
    pump = Refuel(x, SEA_LEVEL/2.0, z, 0, COLOR_GREEN);

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
    return a.radius*a.radius + b.radius*b.radius + 2*a.radius*b.radius > (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z-b.z)*(a.z-b.z);
}

bool detect_collision_lite(bounding_box_t a, bounding_box_t b) { // Where b radius is not considered
    return a.radius*a.radius > (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z-b.z)*(a.z-b.z);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(15.0f), 1.0f/1.0f, 0.1f, fov);
    test.projection = glm::ortho(left, right, bottom, top, 1.0f, 500.0f);
}
