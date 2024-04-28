#ifndef ANDROMEDA_VIEW_H
#define ANDROMEDA_VIEW_H

#include <GLFW/glfw3.h>

class View {
public:
	unsigned int WIDTH = 1200;
	unsigned int HEIGHT = 1200;

	GLFWwindow* window;

	bool init();
	void cleanup();
};

#endif
