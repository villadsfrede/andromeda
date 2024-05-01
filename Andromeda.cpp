#include "Andromeda.h"

int main()
{
	// DONT TOUCH THIS //
	
	View view;

	if (!view.init())
	{
		return 0;
	}

	Shader standard = Shader("dependencies/include/resources/default.vert", "dependencies/include/resources/default.frag");

	Camera camera = Camera(0.75, 16 / 9, 0.1, 100);

	Universe universe;

	while (!glfwWindowShouldClose(view.window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		standard.useProgram();

		camera.input(view.window);

		camera(standard, "camera");

		universe.render();

		glfwSwapBuffers(view.window);

		glfwPollEvents();
	}

	view.cleanup();
	return 0;
}