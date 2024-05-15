#include "Andromeda.h"

int main()
{
	View view;

	if (!view.init())
	{
		return 0;
	}

	// Setup sphere shader
	Shader sphere = Shader("default.vert", "default.frag");

	// create camere and universe
	view.camera = std::make_unique<Camera>(0.75f, 16 / 9, 0.1f, 10e5f);
	view.universe = std::make_unique<Universe>(100, 5.9724e24, 10e9, 1000e9, 10e3, 50e3, 0);

	// loop while running
	while (!glfwWindowShouldClose(view.window))
	{
		// Clear with backgroundcolor
		glClearColor(view.bg[0], view.bg[1], view.bg[2], view.bg[3]);

		// Clear color and depth bit
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handle camera inputs
		view.camera->input(view.window);

		sphere.useProgram();

		view.camera->uniform(sphere);

		// [space] --> update universe
		if (glfwGetKey(view.window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			view.universe->update();
		}

		view.universe->render();
		
		view.renderUI();

		// Double buffering so swap
		glfwSwapBuffers(view.window);

		// Get next events
		glfwPollEvents();
	}

	// Free all memory
	sphere.cleanup();
	view.universe->cleanup();
	view.cleanup();

	return 0;
}