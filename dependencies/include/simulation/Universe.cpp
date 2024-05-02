#include <stdlib.h>
#include <iostream>
#include "Universe.h"

void Universe::generate()
{
	for (unsigned int i = 0; i < objects; i++)
	{
		masses[i] = 100;

		positions[3 * i + 0] = (100 * ((float)rand() / (float)RAND_MAX)) - 50;
		positions[3 * i + 1] = (100 * ((float)rand() / (float)RAND_MAX)) - 50;
		positions[3 * i + 2] = (100 * ((float)rand() / (float)RAND_MAX)) - 50;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
}

void Universe::update()
{
	for (size_t i = 0; i < objects; i++) 
	{
		float acceleration[3] = { 0 };

		for (size_t j = 0; j < objects; j++)
		{
			if (i != j)
			{
				float direction[3];

				direction[0] = positions[3 * i + 0] - positions[3 * j + 0];
				direction[1] = positions[3 * i + 1] - positions[3 * j + 1];
				direction[2] = positions[3 * i + 2] - positions[3 * j + 2];

				float magnitude = sqrt(direction[0] * direction[0] + direction[1] * direction[1] + direction[2] * direction[2]);

				float unit[3] = {
					direction[0] / magnitude,
					direction[1] / magnitude,
					direction[2] / magnitude,
				};

				float total = -1.0 * G * masses[j] / (magnitude * magnitude + 4);

				acceleration[0] = acceleration[0] + total * unit[0];
				acceleration[1] = acceleration[1] + total * unit[1];
				acceleration[2] = acceleration[2] + total * unit[2];
			}
		}

		velocities[3 * i + 0] = velocities[3 * i + 0] + acceleration[0] * dt;
		velocities[3 * i + 1] = velocities[3 * i + 1] + acceleration[1] * dt;
		velocities[3 * i + 2] = velocities[3 * i + 2] + acceleration[2] * dt;
	}

	for (size_t i = 0; i < objects; i++)
	{
		positions[3 * i + 0] = positions[3 * i + 0] + velocities[3 * i + 0] * dt;
		positions[3 * i + 1] = positions[3 * i + 1] + velocities[3 * i + 1] * dt;
		positions[3 * i + 2] = positions[3 * i + 2] + velocities[3 * i + 2] * dt;
	}

	t = t + dt;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
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