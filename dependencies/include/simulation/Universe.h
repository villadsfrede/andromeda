#ifndef ANDROMEDA_UNIVERSE_H
#define ANDROMEDA_UNIVERSE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Universe {
public:
	float start = 0;
	float t = 0;
	float end = 86400 * 365 * 10;

	float dt = 3600;

	float G = 6.67e-11;

	static const int objects = 10;
	
	float masses[objects] = { 0 };
	float velocities[3 * objects] = { 0 };
	float positions[3 * objects] = { 0 };

	GLuint vbo, vao;

	void generate();
	void update();
	void render();
	void cleanup();

	Universe();
};

#endif
