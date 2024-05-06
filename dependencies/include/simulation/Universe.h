#ifndef ANDROMEDA_UNIVERSE_H
#define ANDROMEDA_UNIVERSE_H

#include <vector>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Body.h"
#include "Algorithm.h"
#include "BarnesHut.h"

class Universe {
private:
	GLuint vbo[3], vao;

	std::unique_ptr<Algorithm> algorithm;

public:
	static const int objects = 3;

	std::vector<std::shared_ptr<Body>> body;

	Universe();

	void generate();
	void update();
	void render();
	void cleanup();
};

#endif
