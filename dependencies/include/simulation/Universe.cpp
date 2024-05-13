#include "Universe.h"

Universe::Universe(int o, double m, double pmin, double pmax, double vmin, double vmax) : objects(o), mass(m), pmin(pmin), pmax(pmax), vmin(vmin), vmax(vmax)
{
	algorithm = std::make_unique<BarnesHut>(body);

	body.clear();

	srand(0);

	for (int i = 0; i < objects; i++)
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

		body.push_back(std::make_shared<Body>(MEARTH, Vector(x, y, z), Vector(vx, vy, vz), Vector(0, 0, 0), true));
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * objects * 3, nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	buffer();
}

void Universe::buffer()
{
	vertices.clear();

	for (auto& b : body)
	{
		vertices.push_back((float)b->position.x * (float)5000 / 1e13);
		vertices.push_back((float)b->position.y * (float)5000 / 1e13);
		vertices.push_back((float)b->position.z * (float)5000 / 1e13);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * objects * 3, &vertices[0]);
}

/*
void Universe::generate()
{
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
*/

void Universe::update()
{
	algorithm->update();

	buffer();
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
