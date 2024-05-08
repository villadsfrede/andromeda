#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <glm/glm.hpp>
#include "Universe.h"

Universe::Universe()
{
	algorithm = std::make_unique<BarnesHut>(body);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

void Universe::generate()
{
	body.clear();

	srand(0);

	for (unsigned int i = 0; i < OBJECTS; i++)
	{
		float radial = (MAX - MIN) * ((float)rand() / (float)RAND_MAX) + MIN;
		float polar = 2 * PI * ((float)rand() / (float)RAND_MAX);
		float azimuthal = 2 * PI * ((float)rand() / (float)RAND_MAX);

		float x = radial * std::sin(azimuthal) * std::cos(polar);
		float y = radial * std::sin(azimuthal) * std::sin(polar);
		float z = radial * std::cos(azimuthal);

		body.push_back(std::make_shared<Body>(MEARTH, glm::vec3(x, y, z), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)));
	}
}

void Universe::update()
{
	algorithm->update();

	unsigned int i = 0;

	float xScale = DWIDTH / SWIDTH;
	float yScale = DHEIGHT / SHEIGHT;
	float zScale = DDEPTH / SDEPTH;

	//std::cout << xScale << std::endl;
	//std::cout << yScale << std::endl;
	//std::cout << zScale << std::endl;

	for (auto& b : body)
	{
		vertices[i * 3 + 0] = b->position.x * xScale;
		vertices[i * 3 + 1] = b->position.y * yScale;
		vertices[i * 3 + 2] = b->position.z * zScale;

		//std::cout << vertices[i * 3 + 0] << " " << vertices[i * 3 + 1] << " " << vertices[i * 3 + 2] << std::endl;

		i++;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
}

void Universe::render()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, OBJECTS);
}

void Universe::cleanup()
{
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}
