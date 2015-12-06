//
//  Shader.cpp
//  opengl-series
//
//  Created by Tim Zuercher on 11/21/15.
//
//

#include "Shader.h"


GLchar * Shader::readShaderFile(const char *fileName){
    FILE *fp = NULL;
    GLchar * content = NULL;    
    int length = 0;
    
    //Check for null
    if (fileName == NULL) {
        printf("File Name was empty of NULL!\n");
        exit(EXIT_FAILURE);
    };
    
    fp = fopen(fileName, "rt");
    
    //Check for errors opening file
    if (fp == NULL){
        fprintf(stderr,"Failed to read shader from '%s' file.\n\n",fileName );
        exit(EXIT_FAILURE);   
    };
    
    //Get File Length
    fseek(fp, 0, SEEK_END);    
    length = ftell(fp);   
    
    //Move Pointer back to start 
    rewind(fp);
    
    
    if (length > 0){
        //Allocate Space for file with addition of null byte
        content = (GLchar *)malloc(sizeof(char)* (length + 1));
        
        //Read Whole File and append null byte
        if (content != NULL){
            length = fread(content, sizeof(char), length, fp);
            content[length] = '\0';
        }
    }
    
    fclose(fp);
    
    //Check for Any errors
    if (content == NULL){
        fprintf(stderr,"Failed to read shader from '%s' file.\n\n",fileName );
        exit(EXIT_FAILURE);
    }
    
    return content;
}



void Shader::checkErrors(string fileName){
    //Check for Compile Errors
    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    
    if (success == GL_FALSE){
        //Get Length of Error Log
        printf("Compilation Failed for %s.\n",fileName.c_str());
        GLint length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);        
        if (length > 0)
        {
            //Read Error
            char * log = new char[length];
            GLsizei written;
            glGetShaderInfoLog(shaderID, length, &written, log);
            //Print Error
            fprintf(stderr, "log:\n%s\n\n", log );
            delete[] log;
            //exit(EXIT_FAILURE);
        }
    }
}

Shader::Shader(string file, GLenum type){
    shaderID = glCreateShader(type);
    //Read Shader from file
    
    Logger::log("Reading Source from file");
    GLchar * source = readShaderFile(file.c_str());
    Logger::log("Reading complete");
    
    
    //Link shader to source
    Logger::log("Linking Source to Shader");
    glShaderSource(shaderID, 1, (const GLchar **)&source, NULL);
    free(source);
    Logger::log("Linking Complete");
    
    char buff[255];
    snprintf(buff, sizeof(buff), "Compiling Shader '%s' as %s", file.c_str(), getShaderType(type).c_str());
    Logger::log(buff);
    glCompileShader(shaderID);
    checkErrors(file);
    Logger::log("Compiliation Complete\n");
}

string Shader::getShaderType(GLenum type){
    switch (type) {
        case GL_VERTEX_SHADER:
            return "Vertex Shader";
        case GL_FRAGMENT_SHADER:
            return "Fragment Shader";
        case GL_GEOMETRY_SHADER:
            return "Geometry Shader";
        case GL_TESS_CONTROL_SHADER:
            return "Tesselation Control Shader";
        case GL_TESS_EVALUATION_SHADER:
            return "Tesselation Evaluation Shader";
        default:
            return "Unknown Type";
    }
}


