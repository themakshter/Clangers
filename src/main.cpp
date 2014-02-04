#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "object.h"
#include "util.h"
#include "camera.h"

using namespace std;
using namespace glm;

class Scene
{
private:
    int running;
public:
    Scene() {};
    void run();
};

GLuint vertexShader, fragmentShader;
GLuint objectProgram, skyboxProgram;
GLFWwindow* window;

Camera camera = Camera();

Scene scene = Scene();

bool increasingSpeed = false;
bool decreasingSpeed = false;
bool rotatingLeft = false;
bool rotatingRight = false;
bool rotatingUp = false;
bool rotatingDown = false;

int tourPart;

bool raisingClanger,loweringClanger,waitingClanger;

float clangerHeight,delay;

bool tour;
bool raising1Camera, rotating1Camera, accelerating1Camera, decelerating1Camera, rotating2Camera, lowering1Camera;
bool partOne,partTwo,partThree,partFour,partFive,partSix,partSeven,partEight;
float cameraHeight, cameraAngle, cameraSpeed;

const float speed = 5;

void Scene::run()
{

    //Skybox
    Object skybox1("objects/skybox1.obj","textures/space-earth.bmp");

    Object skybox2("objects/skybox2.obj","textures/space.bmp");

    Object skybox3("objects/skybox3.obj","textures/space.bmp");

    Object skybox4("objects/skybox4.obj","textures/space-mars.bmp");

    Object ceiling1("objects/ceiling.obj","textures/space.bmp");

    //Clangers text
    Object clangerText("objects/clangers-text.obj","textures/clangers-text.bmp");

    //standing clangers
    Object standingClanger1("objects/clanger-standing1.obj","textures/clanger.bmp");

    Object standingClanger2("objects/clanger-standing2.obj","textures/clanger.bmp");

    //clangers in boats
    Object boatClanger1("objects/clanger-in-boat1.obj","textures/clanger.bmp");

    Object boatClanger2("objects/clanger-in-boat2.obj","textures/clanger.bmp");

    //boats
    Object boat1("objects/clanger-boat1.obj","textures/clanger-boat.bmp");

    Object boat2("objects/clanger-boat2.obj","textures/clanger-boat.bmp");

    //clangers in craters
    Object craterClanger1("objects/clanger-in-crater1.obj","textures/clanger.bmp");

    Object craterClanger2("objects/clanger-in-crater2.obj","textures/clanger.bmp");

    //crater-tops
    Object craterTop1("objects/crater-top1.obj","textures/crater-top.bmp");

    Object craterTop2("objects/crater-top2.obj","textures/crater-top.bmp");

    Object craterTop3("objects/crater-top3.obj","textures/crater-top.bmp");

    //moon landscape
    Object landscape("objects/landscape.obj","textures/moon.bmp");

    glUseProgram(skyboxProgram);
    GLuint skyboxMatrixID = glGetUniformLocation(skyboxProgram, "MVP");

    glUseProgram(objectProgram);
    GLuint objectMatrixID = glGetUniformLocation(objectProgram, "MVP");

    vec4 lightV = vec4(0.f, 0.f, .8f, 1.f);
    GLuint lightVID = glGetUniformLocation(objectProgram, "lightV");
    glUniform4fv(lightVID, 1, &lightV[0]);

    vec4 lightC = vec4(0.2f, .2f, .2f, 1.f);
    GLuint lightCID = glGetUniformLocation(objectProgram, "lightC");
    glUniform4fv(lightCID, 1, &lightC[0]);

    raisingClanger = true;
    loweringClanger = waitingClanger = false;
    accelerating1Camera = true;

    //running
    running = GL_TRUE;
    double oldTime = glfwGetTime(), currentTime = 0, timeDiff = 0;
    while( running )
    {
        currentTime = glfwGetTime();
        timeDiff = currentTime-oldTime;
        oldTime = currentTime;
        if (increasingSpeed)
        {
            camera.increaseSpeed(timeDiff);
        }
        if (decreasingSpeed)
        {
            camera.decreaseSpeed(timeDiff);
        }
        camera.move(timeDiff);
        if (rotatingLeft)
        {
            camera.left(timeDiff);
        }
        if (rotatingRight)
        {
            camera.right(timeDiff);
        }
        if (rotatingUp)
        {
            camera.raise(timeDiff/2);
        }
        if (rotatingDown)
        {
            camera.lower(timeDiff/2);
        }

        if (tour)
        {
            switch(tourPart)
            {
            case 1:
                cameraSpeed += timeDiff;
                camera.increaseSpeed(timeDiff);
                if(cameraSpeed > 4)
                {
                    camera.resetSpeed();
                    cameraSpeed = 0;
                    tourPart = 2;
                }
                break;
            case 2:
                cameraAngle += timeDiff/10;
                camera.right(timeDiff/10);
                if(cameraAngle >= 0.7)
                {
                    cameraAngle = 0;
                    tourPart = 3;
                }
                break;
            case 3:
                cameraAngle +=timeDiff/2;
                camera.left(timeDiff/2);
                if(cameraAngle >= 1.3)
                {
                    cameraAngle = 0;
                    tourPart = 4;
                }
                break;
            case 4:
                cameraSpeed += timeDiff;
                camera.increaseSpeed(timeDiff);
                if(cameraSpeed > 3.5)
                {
                    camera.resetSpeed();
                    cameraSpeed = 0;
                    tourPart = 5;
                }
                break;
            case 5:
                cameraAngle +=timeDiff/2;
                camera.left(timeDiff/2);
                if(cameraAngle >= 1.9)
                {
                    cameraAngle = 0;
                    tourPart = 6;
                }
                break;
            case 6:
                cameraSpeed += timeDiff;
                camera.increaseSpeed(timeDiff);
                if(cameraSpeed > 4.5)
                {
                    camera.resetSpeed();
                    cameraSpeed = 0;
                    tourPart = 7;
                }
                break;
            case 7:
                cameraAngle += timeDiff/2;
                camera.right(timeDiff/2);
                if(cameraAngle >= 0.6)
                {
                    cameraAngle = 0;
                    tourPart = 8;
                }
                break;
            case 8:
                cameraHeight += timeDiff/25;
                camera.raise(timeDiff/25);
                if(cameraHeight>=0.3)
                {
                    cameraHeight = 0;
                    tourPart = 9;
                }
                break;
            case 9:
                cameraAngle += timeDiff/2;
                camera.right(timeDiff/2);
                if(cameraAngle >=4.0)
                {
                    cameraAngle = 0;
                    tourPart = 0;
                }
                break;
            default:
                camera.resetSpeed();
                tour= false;
                break;
            }
        }

        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //using shaders for our skybox
        glUseProgram(skyboxProgram);

        //skybox
        mat4 MVP = camera.getMVP(skybox1.getMatrix());
        glUniformMatrix4fv(skyboxMatrixID, 1, GL_FALSE, &MVP[0][0]);
        skybox1.render();

        MVP = camera.getMVP(skybox2.getMatrix());
        glUniformMatrix4fv(skyboxMatrixID, 1, GL_FALSE, &MVP[0][0]);
        skybox2.render();

        MVP = camera.getMVP(skybox3.getMatrix());
        glUniformMatrix4fv(skyboxMatrixID, 1, GL_FALSE, &MVP[0][0]);
        skybox3.render();

        MVP = camera.getMVP(skybox4.getMatrix());
        glUniformMatrix4fv(skyboxMatrixID, 1, GL_FALSE, &MVP[0][0]);
        skybox4.render();

        MVP = camera.getMVP(ceiling1.getMatrix());
        glUniformMatrix4fv(skyboxMatrixID, 1, GL_FALSE, &MVP[0][0]);
        ceiling1.render();

        //landscape
        glUseProgram(objectProgram);
        MVP = camera.getMVP(landscape.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        landscape.render();

        //clangers text
        MVP = camera.getMVP(clangerText.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        clangerText.render();

        //standing clangers
        MVP = camera.getMVP(standingClanger1.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        standingClanger1.render();

        MVP = camera.getMVP(standingClanger2.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        standingClanger2.render();

        //clangers in boats
        MVP = camera.getMVP(boatClanger1.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        boatClanger1.render();

        MVP = camera.getMVP(boatClanger2.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        boatClanger2.render();

        //clanger boats
        MVP = camera.getMVP(boat1.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        boat1.render();

        MVP = camera.getMVP(boat2.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        boat2.render();

        //clangers in craters
        MVP = camera.getMVP(craterClanger1.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        craterClanger1.render();

        MVP = camera.getMVP(craterClanger2.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        craterClanger2.render();


        //crater-tops
        MVP = camera.getMVP(craterTop2.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        craterTop2.render();

        MVP = camera.getMVP(craterTop1.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        craterTop1.render();

        MVP = camera.getMVP(craterTop3.getMatrix());
        glUniformMatrix4fv(objectMatrixID, 1, GL_FALSE, &MVP[0][0]);
        craterTop3.render();


        //rotating clangers text
        clangerText.translate(vec3(-0.07719,-0.0423,-1.09915));
        clangerText.rotate(timeDiff * 100,vec3(0,1,0));
        clangerText.translate(vec3(0.07719,0.0423,1.09915));

        //boat rotating around the origin but only in x axis
        boatClanger1.translate(vec3(-0.07719,-0.0423,-1.09915));
        boat1.translate(vec3(-0.07719,-0.0423,-1.09915));

        boatClanger1.rotate(timeDiff * 30,vec3(0,-1,0));
        boat1.rotate(timeDiff * 30,vec3(0,-1,0));

        boatClanger1.translate(vec3(0.07719,0.0423,1.09915));
        boat1.translate(vec3(0.07719,0.0423,1.09915));


        //animation for rasing and lowering clanger
        if(raisingClanger)
        {
            clangerHeight += timeDiff * (clangerHeight + 0.01);
            craterClanger1.translate(vec3(0,timeDiff * (clangerHeight + 0.01),0));
            if(clangerHeight >= 0.08)
            {
                raisingClanger=false;
                waitingClanger = true;
            }
        }

        //wait in the middle
        if(waitingClanger)
        {
            delay += timeDiff;
            if(delay >= 1)
            {
                waitingClanger=false;
                loweringClanger = true;
            }
        }

        //lowering clanger
        if(loweringClanger)
        {
            clangerHeight -= timeDiff * (clangerHeight + 0.01);
            craterClanger1.translate(vec3(0,-timeDiff * (clangerHeight + 0.01),0));
            if(clangerHeight <= 0)
            {
                loweringClanger=false;
                raisingClanger= true;
            }

        }

        glFlush();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}



static void keyHandler(GLFWwindow* window,int key, int scancode,int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE || key == 'Q' || key == 'q')
        {
            glfwTerminate();
            exit(EXIT_SUCCESS);
        }
        switch(key)
        {
        case GLFW_KEY_UP:
            increasingSpeed = true;
            break;
        case GLFW_KEY_DOWN:
            decreasingSpeed = true;
            break;
        case GLFW_KEY_RIGHT:
            rotatingRight = true;
            break;
        case GLFW_KEY_LEFT:
            rotatingLeft = true;
            break;
        case GLFW_KEY_PAGE_UP:
            rotatingUp = true;
            break;
        case GLFW_KEY_PAGE_DOWN:
            rotatingDown = true;
            break;
        case GLFW_KEY_SPACE:
            camera.resetSpeed();
            break;
        case 'P':
            ;
        case 'p':
            camera.jumpTo(vec3(0.0f, 0.05f, 0.5f));
            camera.lookAt(180.6);
            break;
        case 'T':
            ;
        case 't':
        {
            tour = true;
            tourPart = 1;
            cameraHeight = cameraAngle = cameraSpeed = 0;
            camera.jumpTo(vec3(0.0f, 0.05f, 0.5f));
            camera.lookAt(180.6);
            break;
        }
        case 'E':
            ;
        case 'e':
        {
            tour = false;
            camera.resetSpeed();
            cameraHeight = cameraAngle = cameraSpeed = 0;
            camera.jumpTo(vec3(0.0f, 0.00f, 0.0f));
            camera.lookAt(180.6);
            break;
        }
        }
    }
    else if (action == GLFW_RELEASE)
    {
        switch(key)
        {
        case GLFW_KEY_UP:
            increasingSpeed = false;
            break;
        case GLFW_KEY_DOWN:
            decreasingSpeed = false;
            break;
        case GLFW_KEY_RIGHT:
            rotatingRight = false;
            break;
        case GLFW_KEY_LEFT:
            rotatingLeft = false;
            break;
        case GLFW_KEY_PAGE_UP:
            rotatingUp = false;
            break;
        case GLFW_KEY_PAGE_DOWN:
            rotatingDown = false;
            break;
        }
    }
}

int main(void)
{
    printf("Initialising... \n");

    if (!glfwInit())
    {
        printf("Could not initialise GLFW\n");
        exit(EXIT_FAILURE);
    }


    glfwWindowHint(GLFW_SAMPLES,4); //4x antialiasing

    window = glfwCreateWindow(1024,768,"COMP3004 CW3 - Clangers on the moon", NULL, NULL);

    if (!window)
    {
        printf("Could not open window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //window is fine so make it current context
    glfwMakeContextCurrent(window);

    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK)
    {
        printf("Could not initialise GLEW\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Initialised GLEW\n");
    }

    //Everything works
    fprintf(stdout, "GL INFO : %s\n",glGetString(GL_VERSION));
    glfwSetKeyCallback(window,keyHandler);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    objectProgram = LoadShaders("objectvertexshader.vert", "objectfragmentshader.frag");
    skyboxProgram = LoadShaders("objectvertexshader.vert", "skyboxfragmentshader.frag");

    scene.run();


}
