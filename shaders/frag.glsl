#version 410

in vec3 Color;
//uniform float timer;
//in vec4 gl_FradCoord;
out vec4 FragColor;

void main() {
    FragColor = vec4(Color,1.0);
    //FragColor = vec4(gl_FragCoord.x/500,gl_FragCoord.y/500,0.0 ,1.0);// + 0.5*sin(timer),1.0);
}