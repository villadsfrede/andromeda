#ifndef ANDROMEDA_ROCKET_CPP
#define ANDROMEDA_ROCKET_CPP
#include "Rocket.h"
#include <render/Shader.h>


Rocket::Rocket(float m, glm::vec3 p, glm::vec3 v) : Body(m, p, v) {
	Pos = p;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}

void Rocket::move(glm::vec3 mov, Shader& shader) {
	/*
	GLint offsetLocation = glGetUniformLocation(shader.shaderProgram, "offset");

	for (int i = 0; i < 9; i = i + 3) {
		glUniform3f(offsetLocation, mov.x, mov.y, mov.z);
	};
	*/

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3*6);
	

	
	for (int i = 0; i < 9*6; i = i + 3) {
		vertices[i] += mov.x;
		vertices[i+1] += mov.y;
		vertices[i+2] += mov.z;
	};

	
	std::cout << vertices[0] << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	

};


#endif // !ANDROMEDA_ROCKET_CPP






