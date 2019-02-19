#version 330
precision mediump float;

layout(location = 0) in vec3 vPosition; 
layout(location = 1) in texCoord;

out vec2 uvCoord;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(vPosition, 1.0);
	uvCoord = texCoord;
}
