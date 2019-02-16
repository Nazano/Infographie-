#version 330
precision mediump float; //Medium precision for float. highp and smallp can also be used

layout(location = 0) out vec4 diffuseColor;

//We still use varying because OpenGLES 2.0 (OpenGL Embedded System, for example for smartphones) does not accept "in" and "out"

void main()
{
   diffuseColor = vec4(0.2,0.6,0.4,1);
}
