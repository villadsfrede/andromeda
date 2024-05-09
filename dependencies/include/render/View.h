#ifndef ANDROMEDA_VIEW_H
#define ANDROMEDA_VIEW_H

#include <memory>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "simulation/Config.h"
#include "Camera.h"

class View {
public:
	GLFWwindow* window;

	float bg[4] = {0.0f, 0.0f, 0.0f, 1.0f};

	std::unique_ptr<Camera> camera;

	bool init();
	void renderUI();
	void cleanup();
};

#endif
