#version 330
precision mediump float; //Medium precision for float. highp and smallp can also be used

in vec2 uvCoord;
in vec3 pos;

out vec4 color;

uniform sampler2D myTex;

void main()
{
   color = texture( myTex, uvCoord);
}
