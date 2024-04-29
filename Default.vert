#version 330 core
layout (location = 0) in vec3 Pos;
void main(){

	gl_Positions = vec4(aPos, 1.0);
	vertexColor = vec4(1.0, 0.0, 0.0, 1.0);
}