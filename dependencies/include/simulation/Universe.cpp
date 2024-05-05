#include <stdlib.h>
#include <iostream>
#include <glm/glm.hpp>
#include "Universe.h"
#include "Octree.h"

void Universe::generate()
{
	float min = 99;
	float max = 100;

	float PI = 3.1415926535897932385;

	for (unsigned int i = 0; i < objects; i++)
	{
		float radial = (max - min) * ((float)rand() / (float)RAND_MAX) + min;
		float polar = 2 * PI * ((float)rand() / (float)RAND_MAX);
		float azimuthal = 2 * PI * ((float)rand() / (float)RAND_MAX);

		posx[i] = radial * std::sin(azimuthal) * std::cos(polar);
		posy[i] = radial * std::sin(azimuthal) * std::sin(polar);
		posz[i] = radial * std::cos(azimuthal);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(posx), posx);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(posy), posy);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(posz), posz);
}

/*
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

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), positions);
}
*/

void Universe::update()
{

}

void Universe::render()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, objects);
}

void Universe::cleanup()
{
	glDisableVertexAttribArray(0);
	glDeleteBuffers(3, vbo);
	glDeleteVertexArrays(1, &vao);
}

Universe::Universe()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(3, vbo);

	glBindVertexArray(vao);

	// POSITION X //

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(posx), posx, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// POSITION Y //

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(posy), posy, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// POSITION Z //

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(posz), posz, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
}