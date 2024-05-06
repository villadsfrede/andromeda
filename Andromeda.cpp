#include "Andromeda.h"
#include "dependencies/include/simulation/Rocket.h"

#include "simulation/Octree.h"

int main()
{
	// DONT TOUCH THIS //
	
	View view;

	if (!view.init())
	{
		return 0;
	}
	Shader Rocket = Shader("dependencies/include/resources/Rocket.vert", "dependencies/include/resources/Rocket.frag");

	Shader sphere = Shader("dependencies/include/resources/default.vert", "dependencies/include/resources/default.frag");

	Camera camera = Camera(0.75f, 16 / 9, 0.1f, 10e5f);

	Universe u = Universe();

	u.generate();

	u.update();

	while (!glfwWindowShouldClose(view.window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.input(view.window);

		sphere.useProgram();

		Rocket.useProgram();

		camera(sphere);

		glfwSwapBuffers(view.window);

		glfwPollEvents();
	}

	view.cleanup();
	return 0;
}