#ifndef ANDROMEDA_VIEW_H
#define ANDROMEDA_VIEW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class View {
public:
	unsigned int WIDTH = 1000;
	unsigned int HEIGHT = 1000;

	GLFWwindow* window;

	bool init();
	void cleanup();
};

#endif
