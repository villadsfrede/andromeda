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

	Universe universe;

	universe.generate();

	while (!glfwWindowShouldClose(view.window))
	{
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		standard.useProgram();

		universe.render();

		glfwSwapBuffers(view.window);

		glfwPollEvents();
	}

	view.cleanup();
	return 0;
}