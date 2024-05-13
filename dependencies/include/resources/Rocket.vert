#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 perspective;
uniform float angle;
uniform vec3 offset;

void main(){

	vec4 totalOffset = vec4(offset.x, offset.y, offset.z, 0.0f);
	gl_Position = perspective * view * vec4(aPos.x + offset.x, aPos.y + offset.y, aPos.z + offset.z, 1.0);
	
}