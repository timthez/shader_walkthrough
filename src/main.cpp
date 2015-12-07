
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


// third-party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


#include "Program.h"


//http://glm.g-truc.net/0.9.2/api/a00001.html
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



using glm::mat4;
using glm::vec3;
using namespace std;





const GLuint SCREEN_WIDTH = 500;
const GLuint SCREEN_HEIGHT = 500;

GLfloat timer;
bool show3d;
Program *program;

GLFWwindow* gWindow = NULL;

GLuint vao;





static void Render() {
    //White Background
    glClearColor(1, 1, 1, 1); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    timer+=0.01;
    GLuint timerLoc = glGetUniformLocation(program->getID(), "timer");
    glUniform1f(timerLoc, timer);
    
    //rotation    
        
    // bind the VAO (the triangle) Modeling Coordinates
    
    // GLuint location = glGetUniformLocation(program->getID(),"gluLookAt");
    // mat4 glulookat = glm::lookAt(vec3(4,3,-3),vec3(0,0,0),vec3(0,1,0));    
    // glUniformMatrix4fv(location,1,GL_FALSE,glm::value_ptr(glulookat));
    
    // mat4 perspective = glm::perspective((GLfloat)60.0,(GLfloat)1.0,(GLfloat)0.001,(GLfloat)1000.0);
    // GLuint locationPer = glGetUniformLocation(program->getID(),"perspective");
    // glUniformMatrix4fv(locationPer,1,GL_FALSE,glm::value_ptr(perspective));
    
    
    if(show3d){
      //Draw Cube 
      glDrawArrays(GL_TRIANGLES,0, 36);        
    }else{
      //Draw Triangle
      glDrawArrays(GL_TRIANGLES, 0, 3);  
    }
   
    glfwSwapBuffers(gWindow);
}
int mainWindow;
//Compile Link and Create Shader Program
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
        program->printActiveUniforms();
    }
}
void createAttributes(float  positionData[],int sizePos, float  colorData[], int sizeColor){
    //Generate vertex buffer objects
    GLuint vboHandles[2];
    glGenBuffers(2,vboHandles);
    
    //Hold onto an vbo id
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];
    
    //Position Binding
    glBindBuffer(GL_ARRAY_BUFFER,positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizePos, positionData, GL_STATIC_DRAW);
    
    
    //Color binding
    glBindBuffer(GL_ARRAY_BUFFER,colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeColor, colorData, GL_STATIC_DRAW);
    
    

    //generate a single vao
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    
    //Link attribute with location or you can do it in the shader
    program->bindAttribLocation(0,"VertexPosition");
    program->bindAttribLocation(1,"VertexColor");
    
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

void triangleSetup(){    
    //Triangle Vertices Coordinates (Model Coordinates)
    float positionData[] ={
        -0.8f,-0.8f,0.0f,
        0.8f,-0.8f,0.0f,
        0.0f,0.8f,0.0f
    };
    //Triangle Vertice Colors
    float colorData[]={
        1.0f,0.0f,0.0f,
        0.0f,0.0f,1.0f,
        0.0f,1.0f,0.0f
    };
    
    createAttributes(positionData, sizeof(positionData), colorData, sizeof(colorData));    
}

void cubeSetup(){    
    //Cube Vertices Coordinates (Model Coordinates)
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
    //Cube vertice colors, one face has 2 triangles with different colors to show that it is made up with triangles
    float colorData[]={
        
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        
        1.000f,  0.000f,  0.000f,
        1.000f,  0.000f,  0.000f,
        1.000f,  0.000f,  0.000f,        
        
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        
        0.800f,  0.000f,  0.000f,
        0.800f,  0.000f,  0.000f,
        0.800f,  0.000f,  0.000f,
        
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        0.583f,  0.771f,  0.014f,
        
        1.000f,  0.000f,  0.000f,
        1.000f,  0.000f,  0.000f,
        1.000f,  0.000f,  0.000f,
        
        0.000f,  1.000f,  0.000f,
        0.000f,  1.000f,  0.000f,
        0.000f,  1.000f,  0.000f,        
        
        0.000f,  1.000f,  0.000f,
        0.000f,  1.000f,  0.000f,
        0.000f,  1.000f,  0.000f,
        
        0.000f,  0.000f,  1.000f,
        0.000f,  0.000f,  1.000f,
        0.000f,  0.000f,  1.000f,
        
        0.000f,  0.000f,  1.000f,
        0.000f,  0.000f,  1.000f,
        0.000f,  0.000f,  1.000f,
        
        1.000f,  0.000f,  0.000f,
        1.000f,  0.000f,  0.000f,
        1.000f,  0.000f,  0.000f,
    };
    createAttributes(positionData, sizeof(positionData), colorData, sizeof(colorData));  
       
    
}

void printInfo(){
    char buff[255];    
    
    //Print OpenGl Info
    Logger::log(ANSI_COLOR_CYAN "*****************************************************************************" ANSI_COLOR_RESET);
    snprintf(buff, sizeof(buff), "OpenGL version: %s", glGetString(GL_VERSION));
    Logger::log(buff);
    
    snprintf(buff, sizeof(buff), "GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    Logger::log(buff);
    
    snprintf(buff, sizeof(buff), "Vendor: %s", glGetString(GL_VENDOR));
    Logger::log(buff);
    
    snprintf(buff, sizeof(buff), "Renderer: %s", glGetString(GL_RENDERER));
    Logger::log(buff);
    
    //Print Window Position Info
    Logger::log(ANSI_COLOR_CYAN"--------------------------------------------------------------------------------" ANSI_COLOR_RESET);
    int xpos, ypos;
    glfwGetWindowPos(gWindow, &xpos, &ypos);
    snprintf(buff, sizeof(buff), "Window Position\n x: %d, y: %d",xpos,ypos);
    Logger::log(buff);
    Logger::log("Set Window Postion in the makefile otherwise it defaults to center of screen.");
    Logger::log(ANSI_COLOR_CYAN "-----------------------------------------------------------------------------" ANSI_COLOR_RESET);    
    Logger::log(ANSI_COLOR_CYAN "********************************************************************************\n" ANSI_COLOR_RESET);

}
void OnError(int errorCode, const char* msg) {
    throw std::runtime_error(msg);
}
void key_press(GLFWwindow* window, int key, int scancode, int action, int mods){
    
    //Recompile Shaders on C key press
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        Logger::log(ANSI_COLOR_MAGENTA "================================================================================");
        Logger::log("                              Recompiling Shaders                               ");
        Logger::log("================================================================================");
        createShaders();
        Logger::log("================================================================================");
        Logger::log("                              Compilation Complete                              ");
        Logger::log("================================================================================ " ANSI_COLOR_RESET);
    }
    //Use the Cube 
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        show3d=true;
        Logger::log(ANSI_COLOR_MAGENTA "================================================================================");
        Logger::log("                              Using Cube                                        ");
        Logger::log("================================================================================" ANSI_COLOR_RESET);
        cubeSetup();
    }
    //Use the Triangle
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        show3d=false;
        triangleSetup();
        Logger::log(ANSI_COLOR_MAGENTA "================================================================================");
        Logger::log("                              Using Triangle                  ");
        Logger::log("================================================================================" ANSI_COLOR_RESET);
    }
}
int main(int argc, char **argv)
{
    Logger::log(ANSI_COLOR_CYAN "################################################################################");
    Logger::log("                              Starting GLFW and OpenGL           ");
    Logger::log("################################################################################" ANSI_COLOR_RESET);
    //Logger::show =false;
    show3d=false;    
    glfwSetErrorCallback(OnError);
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
    
    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    gWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Tutorial", NULL, NULL);
    
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
    
    // print out some info environment
    printInfo();    
    
    
    
    createShaders();
    
    triangleSetup();
    
    //Hide things that are behind others
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    //start timer 
    timer = 0.0;
    
    
    GLuint location = glGetUniformLocation(program->getID(),"screen");
    glUniform2f(location,SCREEN_WIDTH, SCREEN_HEIGHT);
    
    //Handle Key events
    glfwSetKeyCallback(gWindow, key_press);
    //Run Loop
    while(!glfwWindowShouldClose(gWindow)){
            
        glfwPollEvents();
        Render();
    }
    glfwTerminate();
    
    
  
    
    

}

