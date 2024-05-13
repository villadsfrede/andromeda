#ifndef ANDROMEDA_UNIVERSE_H
#define ANDROMEDA_UNIVERSE_H

#include <memory>
#include <vector>
#include <stdlib.h>
#include <cstdlib>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Config.h"
#include "Body.h"
#include "Algorithm.h"
#include "BarnesHut.h"

class Universe {
private:
	int objects;
	double mass;
	double pmin;
	double pmax;
	double vmin;
	double vmax;

	GLuint vao, vbo;

	std::unique_ptr<Algorithm> algorithm;

public:
	std::vector<std::shared_ptr<Body>> body;

	std::vector<float> vertices;

	Universe();

	void generate();
	void update();
	void buffer();
	void render();
	void cleanup();
};

#endif
