#ifndef ANDROMEDA_VIEW_H
#define ANDROMEDA_VIEW_H

#include <memory>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "simulation/Universe.h"

class View {
private:
	// Window width and height
	static const unsigned short int WWIDTH = 1000;
	static const unsigned short int WHEIGHT = 1000;

	// Setting variables
	int objects = 1;
	float mass;
	float pmin = 10e9;
	float pmax = 1000e9;
	float vmin = 1e3;
	float vmax = 50e3;
	int seed = 0;

	// File path
	char file[64] = "universe.txt";

public:
	GLFWwindow* window;

	// Background color
	float bg[4] = {0.0f, 0.0f, 0.0f, 1.0f};

	// Current camera
	std::unique_ptr<Camera> camera;

	// Current universe
	std::unique_ptr<Universe> universe = nullptr;

	bool init();
	// Render UI elements
	void renderUI();
	// Free memory
	void cleanup();
};

#endif
