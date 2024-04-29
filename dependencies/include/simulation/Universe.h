#ifndef ANDROMEDA_UNIVERSE_H
#define ANDROMEDA_UNIVERSE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Universe {
public:
	float masses[100];
	float velocities[3 * 100];
	float positions[3 * 100];

	GLuint vbo, vao;

	void generate();
	void render();
	void cleanup();

	Universe();
};

#endif
