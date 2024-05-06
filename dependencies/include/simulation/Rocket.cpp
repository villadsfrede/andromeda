#ifndef ANDROMEDA_ROCKET_CPP
#define ANDROMEDA_ROCKET_CPP
#include "Rocket.h"
#include <render/Shader.h>


Rocket::Rocket(float m, glm::vec3 p, glm::vec3 v) : Body(m, p, v) {
	Pos = p;
}

void Rocket::draw() {
	float vertices[] = {

	 0.5f + Pos.x,  0.5f + Pos.y, 0.0f + Pos.z,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f,  0.5f, 0.0f,  // top left 

	

	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);



}



#endif // !ANDROMEDA_ROCKET_CPP






