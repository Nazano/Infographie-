#version 330
precision mediump float; //Medium precision for float. highp and smallp can also be used

layout(location = 0) out vec4 diffuseColor;

in vec2 uvCoord;

uniform sampler2D Texture;

void main()
{
   diffuseColor = texture( Texture, uvCoord).rgb;
}
