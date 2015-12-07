#version 410

in vec3 Color;
uniform float timer;
uniform vec2 screen;
//in vec4 gl_FradCoord;
out vec4 FragColor;

void main() {
    //FragColor = vec4(Color,1.0);
    FragColor = vec4(gl_FragCoord.x/screen.x, gl_FragCoord.y/screen.y,0.5 + 0.5*sin(timer),1.0);
}