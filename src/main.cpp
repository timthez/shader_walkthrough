
// third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "Program.h"
//using namespace glm;

#include <stdio.h>
#include <unistd.h>

//http://glm.g-truc.net/0.9.2/api/a00001.html
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



using glm::mat4;
using glm::vec3;
using namespace std;

GLuint v, f, f2, p;
float lpos[4] = { 1, 0.5, 1, 0 };
float a = 0;
clock_t time0, time1;
float timer5;
GLfloat c;

Program *program;
GLFWwindow* gWindow = NULL;
GLuint vao;





static void Render() {
    //White Background
    glClearColor(1, 1, 1, 1); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //c+=0.01;
    //GLuint timer = glGetUniformLocation(program, "timer");
    //glUniform1f(timer, c);
    
    //rotation
    
    //mat4 rotationMatrix = glm::rotate(mat4(1.0f),90.0f,vec3(0.0f,0.0f,1.0f));
    //GLuint location = glGetUniformLocation(program,"Rotation");
    //rotationMatrix
    //glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(rotationMatrix)); //
    
    
    // bind the VAO (the triangle) Modeling Coordinates
    
    GLuint location = glGetUniformLocation(program->getID(),"gluLookAt");
    mat4 glulookat = glm::lookAt(vec3(4,3,-3),vec3(0,0,0),vec3(0,1,0));
    
    glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(glulookat));
    
    mat4 perspective = glm::perspective((GLfloat)60.0,(GLfloat)1.0,(GLfloat)0.001,(GLfloat)1000.0);
    GLuint locationPer = glGetUniformLocation(program->getID(),"perspective");
    glUniformMatrix4fv(locationPer,1,GL_FALSE,glm::value_ptr(perspective));
    
    
    glBindVertexArray(vao);
    
    // draw the VAO
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES,0, 12 * 3);
    // unbind the VAO
    //glBindVertexArray(0);
    
    // unbind the program
    //glUseProgram(0);
    
    // swap the display buffers (displays what was just drawn)
    glfwSwapBuffers(gWindow);
}
int mainWindow;

void createShaders(){
    Shader vertex("./shaders/vert.glsl",GL_VERTEX_SHADER);
    Shader fragment("./shaders/frag.glsl",GL_FRAGMENT_SHADER);
    
    program = new Program();
    
    program->attachShader(vertex);
    program->attachShader(fragment);
    program->link();
    program->use();
    
    if(Logger::show){
        program->printActiveAttribs();
    }
}

void triangleSetup(){    
    
    float positionData[] ={
        -0.8f,-0.8f,0.0f,
        0.8f,-0.8f,0.0f,
        0.0f,0.8f,0.0f
    };
    // float positionData[] ={
    //     -80.0f,-80.0f,0.5f,
    //     80.0f,-80.0f,0.0f,
    //     0.0f,80.0f,0.0f
    // };
    float colorData[]={
        1.0f,0.0f,0.0f,
        0.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f
    };
    
    GLuint vboHandles[2];
    glGenBuffers(2,vboHandles);
    
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];
    
    //Position Binding
    glBindBuffer(GL_ARRAY_BUFFER,positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);
    
    
    //Color binding
    glBindBuffer(GL_ARRAY_BUFFER,colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);
    
    
    /* Bind Vertexes */

    //generate vao
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    program->bindAttribLocation(0,"VertexPosition");
    //link with location
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    //bind
    glBindBuffer(GL_ARRAY_BUFFER,positionBufferHandle);
    //give data and info about it
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
    //same
    glBindBuffer(GL_ARRAY_BUFFER,colorBufferHandle);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,NULL);    
    
}
void cubeSetup(){    
    
    float positionData[] ={
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };
    float colorData[]={
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };
    
    GLuint vboHandles[2];
    glGenBuffers(2,vboHandles);
    
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];
    
    //Position Binding
    glBindBuffer(GL_ARRAY_BUFFER,positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);
    
    
    //Color binding
    glBindBuffer(GL_ARRAY_BUFFER,colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
    
    
    /* Bind Vertexes */

    //generate vao
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    program->bindAttribLocation(0,"VertexPosition");
    //link with location
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    //bind
    glBindBuffer(GL_ARRAY_BUFFER,positionBufferHandle);
    //give data and info about it
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);
    //same
    glBindBuffer(GL_ARRAY_BUFFER,colorBufferHandle);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,NULL);    
    
}
void printInfo(){
    char buff[255];
    
    //Print Window Position Info
    Logger::log("-----------------------------------------------------------------------------");
    int xpos, ypos;
    glfwGetWindowPos(gWindow, &xpos, &ypos);
    snprintf(buff, sizeof(buff), "Window Position\n x: %d, y: %d",xpos,ypos);
    Logger::log(buff);
    Logger::log("Set Window Postion in the makefile otherwise it defaults to center of screen.");
    Logger::log("-----------------------------------------------------------------------------\n");
    
    
    //Print OpenGl Info
    Logger::log("*****************************************************************************");
    snprintf(buff, sizeof(buff), "OpenGL version: %s", glGetString(GL_VERSION));
    Logger::log(buff);
    
    snprintf(buff, sizeof(buff), "GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    Logger::log(buff);
    
    snprintf(buff, sizeof(buff), "Vendor: %s", glGetString(GL_VENDOR));
    Logger::log(buff);
    
    snprintf(buff, sizeof(buff), "Renderer: %s", glGetString(GL_RENDERER));
    Logger::log(buff);
    
    Logger::log("*****************************************************************************\n");

}
void OnError(int errorCode, const char* msg) {
    throw std::runtime_error(msg);
}
void key_press(GLFWwindow* window, int key, int scancode, int action, int mods){
    
    //Recompile Shaders on C key press
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        createShaders();
    }

    
}
int main(int argc, char **argv)
{
    //Logger::show =false;
        
    glfwSetErrorCallback(OnError);
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
    
    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    gWindow = glfwCreateWindow(500, 500, "OpenGL Tutorial", NULL, NULL);
    
    if(argc >2){
        glfwSetWindowPos(gWindow,atoi(argv[1]),atoi(argv[2]));
    }
    
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);//
    if(!gWindow)
        throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    
    // GLFW settings
    glfwMakeContextCurrent(gWindow);
    
    // initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
    // print out some info about the graphics drivers
    printInfo();
    
    
    
    
    glfwSetKeyCallback(gWindow, key_press);
    
    createShaders();
    
    //triangleSetup();
    cubeSetup();
    // Enable depth test

     glEnable(GL_DEPTH_TEST);

     // Accept fragment if it closer to the camera than the former one

     glDepthFunc(GL_LESS);
    //Run Loop
    while(!glfwWindowShouldClose(gWindow)){
            
        glfwPollEvents();
        Render();
    }
    glfwTerminate();
    
    
  
    
    

}

