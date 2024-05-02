#version 330 core

layout (location = 0) in vec3 vPosition;

uniform mat4 view;
uniform mat4 perspective;
uniform float angle;

void main()
{
	gl_Position = perspective * view * vec4(vPosition, 1.0);
	gl_PointSize = 1000 * (1 / tan(angle / 2)) * 1 / gl_Position.w;
}