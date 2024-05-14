#ifndef ANDROMEDA_VIEW_H
#define ANDROMEDA_VIEW_H

#include <memory>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "simulation/Config.h"
#include "simulation/Universe.h"

class View {
private:
	static const unsigned short int WWIDTH = 1000;
	static const unsigned short int WHEIGHT = 1000;

	int objects;
	float mass;
	float pmin;
	float pmax;
	float vmin;
	float vmax;
	int seed;
	bool barneshut;

	char file[64] = "universe.txt";

public:
	GLFWwindow* window;

	float bg[4] = {0.0f, 0.0f, 0.0f, 1.0f};

	std::unique_ptr<Camera> camera;

	std::unique_ptr<Universe> universe = nullptr;

	bool init();
	void renderUI();
	void cleanup();
};

#endif
