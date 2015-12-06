//
//  Shader.hpp
//  opengl-series
//
//  Created by Tim Zuercher on 11/21/15.
//
//



#include <stdio.h>
#include <string>
#include "Shader.h"

#include <GL/glew.h>
using namespace std;


class Program{
public:
  Program();
  void attachShader(Shader shader);
  void link();
  void use();
  void printActiveAttribs();
  static void resetProgram();
  GLuint getID(){return programID;};
  void bindAttribLocation(GLuint location, const char * name);
private: 
  void checkErrors();
  static string getTypeString(GLenum type);
  GLuint programID;  
};

