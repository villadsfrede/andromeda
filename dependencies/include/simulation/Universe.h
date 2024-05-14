#ifndef ANDROMEDA_UNIVERSE_H
#define ANDROMEDA_UNIVERSE_H

#include <memory>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Constants.h"
#include "Body.h"
#include "Algorithm.h"
#include "DirectSum.h"
#include "BarnesHut.h"

class Universe {
private:
	// Generation parameteres
	int objects;
	double mass;
	double pmin;
	double pmax;
	double vmin;
	double vmax;
	int seed;

	// Buffer IDs
	GLuint vao, vbo;

public:
	// Current algorithm
	std::unique_ptr<Algorithm> algorithm;

	// Bodies in universe
	std::vector<std::shared_ptr<Body>> body;

	// Vector of vertices to be drawn (scaled)
	std::vector<float> vertices;

	// Constructor
	Universe(int o, double m, double pmin, double pmax, double vmin, double vmax, int s);

	// Update positions of bodies
	void update();
	// Load vertices into buffer
	void buffer();
	// Render bodies
	void render();
	// Free memory
	void cleanup();

	void save(char file[]);
	void load(char file[]);
};

#endif
