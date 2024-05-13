#include "Universe.h"

Universe::Universe(int o, double m, double pmin, double pmax, double vmin, double vmax, int s) : objects(o), mass(m), pmin(pmin), pmax(pmax), vmin(vmin), vmax(vmax), seed(s)
{
	algorithm = std::make_unique<BarnesHut>(body);

	body.clear();

	srand(seed);

	for (int i = 0; i < objects; i++)
	{
		double radial = (pmax - pmin) * ((double)rand() / (double)RAND_MAX) + pmin;
		double polar = 2.0 * PI * ((double)rand() / (double)RAND_MAX);
		double azimuthal = 2.0 * PI * ((double)rand() / (double)RAND_MAX);

		double x = radial * std::sin(azimuthal) * std::cos(polar);
		double y = radial * std::sin(azimuthal) * std::sin(polar);
		double z = radial * std::cos(azimuthal);

		radial = (vmax - vmin) * ((double)rand() / (double)RAND_MAX) + vmin;
		polar = 2.0 * PI * ((double)rand() / (double)RAND_MAX);
		azimuthal = 2.0 * PI * ((double)rand() / (double)RAND_MAX);

		double vx = radial * std::sin(azimuthal) * std::cos(polar);
		double vy = radial * std::sin(azimuthal) * std::sin(polar);
		double vz = radial * std::cos(azimuthal);

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

void Universe::save(char file[])
{
	std::ofstream output(file, std::ios::binary);

	if (output.is_open())
	{
		output << "ANDROMEDA" << std::endl;
		output << objects << std::endl;

		for (auto& b : body)
		{
			output << b->mass << " " << b->position.x << " " << b->position.y << " " << b->position.z << " " << b->velocity.x << " " << b->velocity.y << " " << b->velocity.z << " " << b->dynamic << std::endl;
		}

		output.close();
	}
}

void Universe::load(char file[])
{
	body.clear();
	vertices.clear();

	std::string line;
	
	std::string byte;

	std::ifstream input(file, std::ios::binary);

	if (input.is_open())
	{
		std::getline(input, line);

		if (line == "ANDROMEDA")
		{
			getline(input, line);

			objects = std::stoi(line);

			while (std::getline(input, line))
			{
				std::stringstream s(line);

				std::vector<double> a;

				while (std::getline(s, byte, ' '))
				{
					a.push_back(std::stod(byte));
				}

				body.push_back(std::make_shared<Body>(
					a[0],
					Vector(a[1], a[2], a[3]),
					Vector(a[4], a[5], a[6]),
					Vector(0, 0, 0),
					a[7]));
			}
		}

		input.close();

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * objects * 3, nullptr, GL_DYNAMIC_DRAW);

		buffer();
	}
}