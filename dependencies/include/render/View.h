#ifndef ANDROMEDA_VIEW_H
#define ANDROMEDA_VIEW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "simulation/Config.h"

class View {
public:
	//unsigned int width = WWIDTH;
	unsigned int height = WHEIGHT;

	GLFWwindow* window;

	bool init();
	void cleanup();
};

#endif
