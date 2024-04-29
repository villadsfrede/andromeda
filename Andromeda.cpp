#include "Andromeda.h"

int main()
{
	Universe universe;

	// DONT TOUCH THIS //
	
	View view;

	if (!view.init())
	{
		return 0;
	}

	while (!glfwWindowShouldClose(view.window))
	{
		glClearColor(0.75f, 0.5f, 0.25f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(view.window);

		glfwPollEvents();
	}

	view.cleanup();
	return 0;
}