//
//  Shader.hpp
//  opengl-series
//
//  Created by Tim Zuercher on 11/21/15.
//
//


#include "Logger.h"
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <GL/glew.h>
using namespace std;


class Shader{
public:
    Shader(string file,GLenum type);
    GLuint getID(){return shaderID;};
    string getShaderType(){return shaderType;};
private:
  GLuint shaderID;
  string shaderType;
  GLchar * readShaderFile(const char *fileName);
  bool checkErrors(string fileName);
  static string getShaderType(GLenum type);
  
};

