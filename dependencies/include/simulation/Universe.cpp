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
		double radial = (MAX - MIN) * ((double)rand() / (double)RAND_MAX) + MIN;
		double polar = 2.0 * PI * ((double)rand() / (double)RAND_MAX);
		double azimuthal = 2.0 * PI * ((double)rand() / (double)RAND_MAX);

		double x = radial * std::sin(azimuthal) * std::cos(polar);
		double y = radial * std::sin(azimuthal) * std::sin(polar);
		double z = radial * std::cos(azimuthal);

		double vx = 50e3 * ((double)rand() / (double)RAND_MAX) - 25e3;
		double vy = 50e3 * ((double)rand() / (double)RAND_MAX) - 25e3;
		double vz = 50e3 * ((double)rand() / (double)RAND_MAX) - 25e3;

		//std::cout << x << " " << y << " " << z << std::endl;

		body.push_back(std::make_shared<Body>(MEARTH, Vector(x, y, z), Vector(vx, vy, vz), Vector(0, 0, 0), true));
	}

	body.pop_back();
	body.push_back(std::make_shared<Body>(1.989e30, Vector(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0), false));
	
	//body.push_back(std::make_shared<Body>(0.33011e24, Vector(57.909e9, 0, 0), Vector(0, 47.36e3, 0), Vector(0, 0, 0), true));
	//body.push_back(std::make_shared<Body>(4.8675e24, Vector(108.209e9, 0, 0), Vector(0, 35.02e3, 0), Vector(0, 0, 0), true));
	//body.push_back(std::make_shared<Body>(5.9724e24, Vector(149.596e9, 0, 0), Vector(0, 29.78e3, 0), Vector(0, 0, 0), true));
	//body.push_back(std::make_shared<Body>(0.64171e24, Vector(227.923e9, 0, 0), Vector(0, 24.07e3, 0), Vector(0, 0, 0), true));
	//body.push_back(std::make_shared<Body>(1898.19e24, Vector(778.570e9, 0, 0), Vector(0, 13e3, 0), Vector(0, 0, 0), true));
	//body.push_back(std::make_shared<Body>(568.34e24, Vector(1433.529e9, 0, 0), Vector(0, 13e3, 0), Vector(0, 0, 0), true));
	//body.push_back(std::make_shared<Body>(86.813e24, Vector(2872.463e9, 0, 0), Vector(0, 6.80e3, 0), Vector(0, 0, 0), true));
	//body.push_back(std::make_shared<Body>(102.413e24, Vector(4495.060e9, 0, 0), Vector(0, 5.43e3, 0), Vector(0, 0, 0), true));
}

void Universe::update()
{
	algorithm->update();

	unsigned int i = 0;

	double scale = 5000 / 1e13;

	for (auto& b : body)
	{
		vertices[(i * 3) + 0] = b->position.x * scale;
		vertices[(i * 3) + 1] = b->position.y * scale;
		vertices[(i * 3) + 2] = b->position.z * scale;;

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
