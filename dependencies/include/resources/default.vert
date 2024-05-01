#version 330 core

layout (location = 0) in vec3 vPosition;

uniform mat4 camera;

void main()
{
	gl_Position = camera * vec4(vPosition, 1.0);
}