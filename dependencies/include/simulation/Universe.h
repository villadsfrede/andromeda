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

#include "Config.h"
#include "Body.h"
#include "Algorithm.h"
#include "DirectSum.h"
#include "BarnesHut.h"

class Universe {
private:
	int objects;
	double mass;
	double pmin;
	double pmax;
	double vmin;
	double vmax;
	int seed;

	GLuint vao, vbo;

public:
	std::unique_ptr<Algorithm> algorithm;

	std::vector<std::shared_ptr<Body>> body;

	std::vector<float> vertices;

	Universe(int o, double m, double pmin, double pmax, double vmin, double vmax, int s);

	//void generate();
	void update();
	void buffer();
	void render();
	void cleanup();

	void save(char file[]);
	void load(char file[]);
};

#endif
