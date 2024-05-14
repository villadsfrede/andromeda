#include "Universe.h"

// Constructor
Universe::Universe(int o, double m, double pmin, double pmax, double vmin, double vmax, int s) : objects(o), mass(m), pmin(pmin), pmax(pmax), vmin(vmin), vmax(vmax), seed(s)
{
	// Set algorithm
	algorithm = std::make_unique<BarnesHut>(body);

	body.clear();

	// Set random seed
	srand(seed);

	// Generate all bodies
	for (int i = 0; i < objects; i++)
	{
		// Spherical coordinates
		// https://en.wikipedia.org/wiki/Spherical_coordinate_system

		// position
		double radial = (pmax - pmin) * ((double)rand() / (double)RAND_MAX) + pmin;
		double polar = 2.0 * PI * ((double)rand() / (double)RAND_MAX);
		double azimuthal = 2.0 * PI * ((double)rand() / (double)RAND_MAX);

		double x = radial * std::sin(azimuthal) * std::cos(polar);
		double y = radial * std::sin(azimuthal) * std::sin(polar);
		double z = radial * std::cos(azimuthal);

		// velocity
		radial = (vmax - vmin) * ((double)rand() / (double)RAND_MAX) + vmin;
		polar = 2.0 * PI * ((double)rand() / (double)RAND_MAX);
		azimuthal = 2.0 * PI * ((double)rand() / (double)RAND_MAX);

		double vx = radial * std::sin(azimuthal) * std::cos(polar);
		double vy = radial * std::sin(azimuthal) * std::sin(polar);
		double vz = radial * std::cos(azimuthal);

		// create body
		body.push_back(std::make_shared<Body>(MEARTH, Vector(x, y, z), Vector(vx, vy, vz), Vector(0, 0, 0), true));
	}

	// Generate Vertex Array and Array Buffer
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	// using vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// set size of buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * objects * 3, nullptr, GL_DYNAMIC_DRAW);

	// Set attributepointer for use in shaders
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Enable attributepointer
	glEnableVertexAttribArray(0);

	buffer();
}

void Universe::buffer()
{
	vertices.clear();

	for (auto& b : body)
	{
		// Scale and add the position of a body to vertices
		vertices.push_back((float)b->position.x * (float)5000 / 1e13);
		vertices.push_back((float)b->position.y * (float)5000 / 1e13);
		vertices.push_back((float)b->position.z * (float)5000 / 1e13);
	}

	// using vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// change buffer data
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * objects * 3, &vertices[0]);
}

void Universe::update()
{
	// update bodies with algorithm
	algorithm->update();

	// load new information into buuffer
	buffer();
}

void Universe::render()
{
	// Render buffer as GL_POINTS
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, objects);
}

void Universe::cleanup()
{
	// Free memory
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void Universe::save(char file[])
{
	// Create output stream
	std::ofstream output(file, std::ios::binary);

	if (output.is_open())
	{
		// write header
		output << "ANDROMEDA" << std::endl;
		output << objects << std::endl;

		// write each body
		for (auto& b : body)
		{
			output << b->mass << " " << b->position.x << " " << b->position.y << " " << b->position.z << " " << b->velocity.x << " " << b->velocity.y << " " << b->velocity.z << " " << b->dynamic << std::endl;
		}

		output.close();
	}
}

void Universe::load(char file[])
{
	// clear current bodies and vertices
	body.clear();
	vertices.clear();

	// holds one line
	std::string line;
	
	// holds one parameter
	std::string byte;

	// Create input stream
	std::ifstream input(file, std::ios::binary);

	if (input.is_open())
	{
		// Get first line
		std::getline(input, line);

		if (line == "ANDROMEDA")
		{
			// Get second line
			std::getline(input, line);

			// Set objects
			objects = std::stoi(line);

			// Read till end of file
			while (std::getline(input, line))
			{
				// Create stringstream of current line
				std::stringstream s(line);

				// Attributes
				std::vector<double> a;

				// Go through each attribute in line
				while (std::getline(s, byte, ' '))
				{
					a.push_back(std::stod(byte));
				}

				// Create body with attributes
				body.push_back(std::make_shared<Body>(
					a[0],
					Vector(a[1], a[2], a[3]),
					Vector(a[4], a[5], a[6]),
					Vector(0, 0, 0),
					a[7]));
			}
		}

		input.close();

		// Update buffer size
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * objects * 3, nullptr, GL_DYNAMIC_DRAW);

		// Load new vertices
		buffer();
	}
}