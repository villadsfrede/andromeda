#include <stdlib.h>
#include <iostream>
#include "Universe.h"

void Universe::generate()
{
	for (unsigned int i = 0; i < 3 * 100; i = i + 3)
	{
		positions[i + 0] = (2 * ((float)rand() / (float)RAND_MAX)) - 1;
		positions[i + 1] = (2 * ((float)rand() / (float)RAND_MAX)) - 1;
		positions[i + 2] = (2 * ((float)rand() / (float)RAND_MAX)) - 1;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
}

void Universe::render()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, 100);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}