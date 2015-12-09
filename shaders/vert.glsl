#version 410

//Attributes
in vec3 VertexPosition;
// in vec3 VertexColor;
in vec3 VertexColor;
out vec3 Color;

//Uniforms
uniform mat4 MVP;

void main() {
    Color = VertexColor;
    gl_Position = MVP * vec4(VertexPosition.x, VertexPosition.y, VertexPosition.z, 1.0);      
}



// #version 410

// in vec3 VertexPosition;
// layout (location=1) in vec3 VertexColor;
// //uniform mat4 Rotation;
// out vec3 Color;
// uniform mat4 gluLookAt;
// uniform mat4 perspective;

// mat4 gluOrtho(float left, float right, float bottom, float top, float near, float far){
//   mat4 mat;
  
//   float tx = -(right + left)/(right-left);
//   float ty = -(top + bottom)/(top-bottom);
//   float tz = -(far + near)/(far-near);
  
//   mat[0] = vec4( 2.0/(right-left),  0.0,               0.0,              tx );
//   mat[1] = vec4( 0.0,               2.0/(top-bottom),  0.0,              tx );
//   mat[2] = vec4( 0.0,               0.0,               -2.0/(far-near),  ty );
//   mat[3] = vec4( 0.0,               0.0,               0.0,              1.0 );
//   return transpose(mat);
// }

// mat4 gluOrtho2d(float left, float right, float bottom, float top){
//   return gluOrtho(left,right,bottom,top,-1,1);
// }


// mat4 gluLook(double eyeX,  double eyeY,  double eyeZ,  double centerX,  double centerY,  double centerZ,  double upX,  double upY,  double upZ){
//   vec3 f = normalize(vec3(centerX - eyeX,centerY - eyeY,centerZ - eyeZ));
//   vec3 UP = normalize(vec3(upX,upY,upZ));
//   vec3 s = cross(f,UP);
//   vec3 u = cross(normalize(s),f);
  
//   mat4 mat;
  
//   mat[0] = vec4( s.x, s.y, s.z, 0);
//   mat[1] = vec4( u.x, u.y, u.z, 0);
//   mat[2] = vec4( -f.x, -f.y, -f.z, 0);
//   mat[3] = vec4( 0.0, 0.0, 0.0, 1.0);
  
//   mat4 trans;
//   trans[0]= vec4(1,0,0,-eyeX);
//   trans[1]= vec4(0,1,0,-eyeY);
//   trans[2]= vec4(0,0,1,-eyeZ);
//   trans[3]= vec4(0,0,0,1);
  
//   return transpose(mat)*transpose(trans);
// }

// mat4 gluPerspective(float fovy,  float aspect,  float zNear,  float zFar){
//   mat4 mat;
//   float f= 1/tan(radians(fovy/2.0));
  
//   mat[0] = vec4(f/aspect,0,0,0);
//   mat[1] = vec4(0,f,0,0);
//   mat[2] = vec4(0,0,(zNear+zFar)/(zNear-zFar),(2*zNear*zFar)/(zNear-zFar));
//   mat[3] = vec4(0,0,-1,0);
  
//   return transpose(mat);
// }


// void main() {
//   Color = VertexColor;
//   gl_Position = gluPerspective(60,1,0.001,1000) *  gluLook(4,3,3,0,0,0,0,1,0) * vec4(VertexPosition.x, VertexPosition.y, VertexPosition.z, 1.0);

// }