#version 330
precision mediump float;

in vec3 vPosition; 
in vec2 texCoord;

out vec2 uvCoord;
out vec3 pos;

uniform mat4 MVP;
uniform mat4 ModelMatrix;

void main()
{
	gl_Position = ModelMatrix * MVP * vec4(vPosition, 1.0);
	uvCoord = texCoord;
	pos = vPosition;
	
}
