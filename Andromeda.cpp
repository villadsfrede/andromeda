#include "Andromeda.h"

#include "simulation/Octree.h"

int main()
{
	// DONT TOUCH THIS //
	
	View view;

	if (!view.init())
	{
		return 0;
	}

	Shader sphere = Shader("dependencies/include/resources/default.vert", "dependencies/include/resources/default.frag");

	view.camera = std::make_unique<Camera>(0.75f, 16 / 9, 0.1f, 10e5f);

	Universe u = Universe();

	u.generate();

	while (!glfwWindowShouldClose(view.window))
	{
		glClearColor(view.bg[0], view.bg[1], view.bg[2], view.bg[3]);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		view.camera->input(view.window);

		sphere.useProgram();

		view.camera->uniform(sphere);

		if (glfwGetKey(view.window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			u.update();
		}

		u.render();

		view.renderUI();

		glfwSwapBuffers(view.window);

		glfwPollEvents();
	}

	view.cleanup();
	return 0;
}