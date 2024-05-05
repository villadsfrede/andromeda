#ifndef ANDROMEDA_UNIVERSE_H
#define ANDROMEDA_UNIVERSE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Universe {
public:
	float dt = 3600;

	float G = 6.67e-11;

	static const int objects = 25000;
	
	float posx[objects] = { 0 };
	float posy[objects] = { 0 };
	float posz[objects] = { 0 };

	GLuint vbo[3], vao;

	void generate();
	void update();
	void render();
	void cleanup();

	Universe();

	friend class Octree;
};

#endif
