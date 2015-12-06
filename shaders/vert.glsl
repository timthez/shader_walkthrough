#version 410

in vec3 VertexPosition;
layout (location=1) in vec3 VertexColor;
//uniform mat4 Rotation;
out vec3 Color;
uniform mat4 gluLookAt;
uniform mat4 perspective;

mat4 gluOrtho(float left, float right, float bottom, float top, float near, float far){
  mat4 mat;
  
  float tx = -(right + left)/(right-left);
  float ty = -(top + bottom)/(top-bottom);
  float tz = -(far + near)/(far-near);
  
  mat[0] = vec4( 2.0/(right-left),  0.0,               0.0,              tx );
  mat[1] = vec4( 0.0,               2.0/(top-bottom),  0.0,              tx );
  mat[2] = vec4( 0.0,               0.0,               -2.0/(far-near),  ty );
  mat[3] = vec4( 0.0,               0.0,               0.0,              1.0 );
  return transpose(mat);
}

mat4 gluOrtho2d(float left, float right, float bottom, float top){
  return gluOrtho(left,right,bottom,top,-1,1);
}

void main() {
    Color = VertexColor;
    //if(VertexPosition.x > 0.5){
      mat4 m = gluOrtho(-100.0, 100.0, -100.0, 100.0,0.001,200.0);
      mat4 scaler;
      scaler[0] = vec4( 50.0, 0.0, 0.0, 0.0 );
      scaler[1] = vec4( 0.0, 50.0, 0.0, 0.0 );
      scaler[2] = vec4( 0.0, 0.0, 50.0, 0.0 );
      scaler[3] = vec4( 0.0, 0.0, 0.0, 1.0 );
      //if(VertexPosition.x == -80){
        gl_Position = perspective * gluLookAt   * vec4(VertexPosition.x, VertexPosition.y, VertexPosition.z, 1.0);
      //}else{
       // gl_Position =  vec4(VertexPosition.x/100.0, VertexPosition.y/100.0, VertexPosition.z/100.0 , 1.0);
      //}
    //}else{
    //  gl_Position =  vec4(VertexPosition.x + 1.0, VertexPosition.y, VertexPosition.z, 1.0);
    //}
}