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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * objects * 3, nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

void Universe::generate()
{
	body.clear();

	float min = 10;
	float max = 1000;

	float PI = 3.1415926535897932385;

	srand(0);

	for (unsigned int i = 0; i < 100; ++i)
	{
		float radial = (max - min) * ((float)rand() / (float)RAND_MAX) + min;
		float polar = 2 * PI * ((float)rand() / (float)RAND_MAX);
		float azimuthal = 2 * PI * ((float)rand() / (float)RAND_MAX);

		float x = radial * std::sin(azimuthal) * std::cos(polar);
		float y = radial * std::sin(azimuthal) * std::sin(polar);
		float z = radial * std::cos(azimuthal);

		body.push_back(std::make_shared<Body>(1, glm::vec3(x, y, z), glm::vec3(0, 0, 0)));
	}
}

void Universe::update()
{
	algorithm->update();

	for (auto& b : body)
	{
		m_vertices.push_back(b->position.x);
		m_vertices.push_back(b->position.y);
		m_vertices.push_back(b->position.z);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * m_vertices.size(), &m_vertices[0]);
}

void Universe::render()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, objects);
}

void Universe::cleanup()
{
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}
