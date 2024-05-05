#version 330 core

layout (location = 0) in float x;
layout (location = 1) in float y;
layout (location = 2) in float z;

uniform mat4 view;
uniform mat4 perspective;
uniform float angle;

void main()
{
	gl_Position = perspective * view * vec4(x, y, z, 1.0);
	gl_PointSize = 1000 * (1 / tan(angle / 2)) * 1 / gl_Position.w;
}