#include "Program.h"



Program::Program(){
  programID = glCreateProgram();
}

void Program::attachShader(Shader shader){
  glAttachShader(programID, shader.getID());
}

void Program::checkErrors(){
  GLint success;
  glGetProgramiv(programID, GL_LINK_STATUS, &success);
  
  if (success == GL_FALSE){
      //Get Length of Error Log
      printf("Link Failed.\n");
      GLint length;
      glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);        
      if (length > 0)
      {
          //Read Error
          char * log = new char[length];
          GLsizei written;
          glGetProgramInfoLog(programID, length, &written, log);
          //Print Error
          fprintf(stderr, "%s\n\n",log);
          delete[] log;
          //exit(EXIT_FAILURE);
      }
  }
}


void Program::link(){
  glLinkProgram(programID);
  checkErrors();
}

void Program::use(){
  glUseProgram(programID);
}

void Program::resetProgram(){
  glUseProgram(0);  
}

void Program::printActiveAttribs(){  
  
  GLint written, size, location, maxLength, nAttribs;
  GLenum type;
  GLchar * name;
  
  //Get max attribute name length
  glGetProgramiv(programID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
  
  //Get number of Attributes
  glGetProgramiv(programID, GL_ACTIVE_ATTRIBUTES, &nAttribs);
  
  name = (GLchar *) malloc( maxLength );
  
  printf("Active Shader Attributes\n");
  printf("------------------------\n");
  for( int i = 0; i < nAttribs; i++ ) {
      //Get attribute information
      glGetActiveAttrib( programID, i, maxLength, &written, &size, &type, name );
      //Get Location Value
      location = glGetAttribLocation(programID, name);
      //Print Attribute Info
      printf("%d - %s (%s)\n",location, name,getTypeString(type).c_str());
  }
  
  free(name);
}

void Program::bindAttribLocation(GLuint location, const char * name){
  glBindAttribLocation(programID, location,name);
}

//Get Shader Datatype Names
string Program::getTypeString(GLenum type){
    switch (type) {
            //4.1
        case    GL_FLOAT: return "float";
        case    GL_FLOAT_VEC2: return "vec2";
        case    GL_FLOAT_VEC3: return "vec3";
        case    GL_FLOAT_VEC4: return "vec4";
        case    GL_DOUBLE: return "double";
        case    GL_DOUBLE_VEC2: return "dvec2";
        case    GL_DOUBLE_VEC3: return "dvec3";
        case    GL_DOUBLE_VEC4: return "dvec4";
        case    GL_INT: return "int";
        case    GL_INT_VEC2: return "ivec2";
        case    GL_INT_VEC3: return "ivec3";
        case    GL_INT_VEC4: return "ivec4";
        case    GL_UNSIGNED_INT: return "unsigned int";
        case    GL_UNSIGNED_INT_VEC2: return "uvec2";
        case    GL_UNSIGNED_INT_VEC3: return "uvec3";
        case    GL_UNSIGNED_INT_VEC4: return "uvec4";
        case    GL_BOOL: return "bool";
        case    GL_BOOL_VEC2: return "bvec2";
        case    GL_BOOL_VEC3: return "bvec3";
        case    GL_BOOL_VEC4: return "bvec4";
        case    GL_FLOAT_MAT2: return "mat2";
        case    GL_FLOAT_MAT3: return "mat3";
        case    GL_FLOAT_MAT4: return "mat4";
        case    GL_FLOAT_MAT2x3: return "mat2x3";
        case    GL_FLOAT_MAT2x4: return "mat2x4";
        case    GL_FLOAT_MAT3x2: return "mat3x2";
        case    GL_FLOAT_MAT3x4: return "mat3x4";
        case    GL_FLOAT_MAT4x2: return "mat4x2";
        case    GL_FLOAT_MAT4x3: return "mat4x3";
        case    GL_DOUBLE_MAT2: return "dmat2";
        case    GL_DOUBLE_MAT3: return "dmat3";
        case    GL_DOUBLE_MAT4: return "dmat4";
        case    GL_DOUBLE_MAT2x3: return "dmat2x3";
        case    GL_DOUBLE_MAT2x4: return "dmat2x4";
        case    GL_DOUBLE_MAT3x2: return "dmat3x2";
        case    GL_DOUBLE_MAT3x4: return "dmat3x4";
        case    GL_DOUBLE_MAT4x2: return "dmat4x2";
        case    GL_DOUBLE_MAT4x3: return "dmat4x3";
            
            //4.2
        case    GL_SAMPLER_1D: return "sampler1D";
        case    GL_SAMPLER_2D: return "sampler2D";
        case    GL_SAMPLER_3D: return "sampler3D";
        case    GL_SAMPLER_CUBE: return "samplerCube";
        case    GL_SAMPLER_1D_SHADOW: return "sampler1DShadow";
        case    GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
        case    GL_SAMPLER_1D_ARRAY: return "sampler1DArray";
        case    GL_SAMPLER_2D_ARRAY: return "sampler2DArray";
        case    GL_SAMPLER_1D_ARRAY_SHADOW: return "sampler1DArrayShadow";
        case    GL_SAMPLER_2D_ARRAY_SHADOW: return "sampler2DArrayShadow";
        case    GL_SAMPLER_2D_MULTISAMPLE: return "sampler2DMS";
        case    GL_SAMPLER_2D_MULTISAMPLE_ARRAY: return "sampler2DMSArray";
        case    GL_SAMPLER_CUBE_SHADOW: return "samplerCubeShadow";
        case    GL_SAMPLER_BUFFER: return "samplerBuffer";
        case    GL_SAMPLER_2D_RECT: return "sampler2DRect";
        case    GL_SAMPLER_2D_RECT_SHADOW: return "sampler2DRectShadow";
        case    GL_INT_SAMPLER_1D: return "isampler1D";
        case    GL_INT_SAMPLER_2D: return "isampler2D";
        case    GL_INT_SAMPLER_3D: return "isampler3D";
        case    GL_INT_SAMPLER_CUBE: return "isamplerCube";
        case    GL_INT_SAMPLER_1D_ARRAY: return "isampler1DArray";
        case    GL_INT_SAMPLER_2D_ARRAY: return "isampler2DArray";
        case    GL_INT_SAMPLER_2D_MULTISAMPLE: return "isampler2DMS";
        case    GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY: return "isampler2DMSArray";
        case    GL_INT_SAMPLER_BUFFER: return "isamplerBuffer";
        case    GL_INT_SAMPLER_2D_RECT: return "isampler2DRect";
        case    GL_UNSIGNED_INT_SAMPLER_1D: return "usampler1D";
        case    GL_UNSIGNED_INT_SAMPLER_2D: return "usampler2D";
        case    GL_UNSIGNED_INT_SAMPLER_3D: return "usampler3D";
        case    GL_UNSIGNED_INT_SAMPLER_CUBE: return "usamplerCube";
        case    GL_UNSIGNED_INT_SAMPLER_1D_ARRAY: return "usampler2DArray";
        case    GL_UNSIGNED_INT_SAMPLER_2D_ARRAY: return "usampler2DArray";
        case    GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE: return "usampler2DMS";
        case    GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY: return "usampler2DMSArray";
        case    GL_UNSIGNED_INT_SAMPLER_BUFFER: return "usamplerBuffer";
        case    GL_UNSIGNED_INT_SAMPLER_2D_RECT: return "usampler2DRect";
        case    GL_IMAGE_1D: return "image1D";
        case    GL_IMAGE_2D: return "image2D";
        case    GL_IMAGE_3D: return "image3D";
        case    GL_IMAGE_2D_RECT: return "image2DRect";
        case    GL_IMAGE_CUBE: return "imageCube";
        case    GL_IMAGE_BUFFER: return "imageBuffer";
        case    GL_IMAGE_1D_ARRAY: return "image1DArray";
        case    GL_IMAGE_2D_ARRAY: return "image2DArray";
        case    GL_IMAGE_2D_MULTISAMPLE: return "image2DMS";
        case    GL_IMAGE_2D_MULTISAMPLE_ARRAY: return "image2DMSArray";
        case    GL_INT_IMAGE_1D: return "iimage1D";
        case    GL_INT_IMAGE_2D: return "iimage2D";
        case    GL_INT_IMAGE_3D: return "iimage3D";
        case    GL_INT_IMAGE_2D_RECT: return "iimage2DRect";
        case    GL_INT_IMAGE_CUBE: return "iimageCube";
        case    GL_INT_IMAGE_BUFFER: return "iimageBuffer";
        case    GL_INT_IMAGE_1D_ARRAY: return "iimage1DArray";
        case    GL_INT_IMAGE_2D_ARRAY: return "iimage2DArray";
        case    GL_INT_IMAGE_2D_MULTISAMPLE: return "iimage2DMS";
        case    GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY: return "iimage2DMSArray";
        case    GL_UNSIGNED_INT_IMAGE_1D: return "uimage1D";
        case    GL_UNSIGNED_INT_IMAGE_2D: return "uimage2D";
        case    GL_UNSIGNED_INT_IMAGE_3D: return "uimage3D";
        case    GL_UNSIGNED_INT_IMAGE_2D_RECT: return "uimage2DRect";
        case    GL_UNSIGNED_INT_IMAGE_CUBE: return "uimageCube";
        case    GL_UNSIGNED_INT_IMAGE_BUFFER: return "uimageBuffer";
        case    GL_UNSIGNED_INT_IMAGE_1D_ARRAY: return "uimage1DArray";
        case    GL_UNSIGNED_INT_IMAGE_2D_ARRAY: return "uimage2DArray";
        case    GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE: return "uimage2DMS";
        case    GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY: return "uimage2DMSArray";
        case    GL_UNSIGNED_INT_ATOMIC_COUNTER: return "atomic_uint";
        default:
            return "undefined";
    }

}