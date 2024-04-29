#include <stdlib.h>
#include <iostream>
#include "Universe.h"

void Universe::generate()
{
	for (unsigned int i = 0; i < 3 * 100; i++)
	{
		positions[i] = (2 * ((float)rand() / (float)RAND_MAX)) - 1;
	}
}

void Universe::render()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, 300);

	std::cout << glGetError() << std::endl;
}

void Universe::cleanup()
{
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

Universe::Universe()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}