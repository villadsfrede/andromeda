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

	Camera camera = Camera(0.75f, 16 / 9, 0.1f, 10e5f);

	Universe u = Universe();

	//Vector v = Vector(0, 0, 0);
	//Vector u = Vector(1, 0, 0);
	//Vector w = v + u;

	//std::cout << "(" << w.x << "," << w.y << "," << w.z << ")" << std::endl;
	//std::cout << (v != u) << std::endl;
	//std::cout << Distance(v, u) << std::endl;

	u.generate();

	

	while (!glfwWindowShouldClose(view.window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.input(view.window);

		sphere.useProgram();

		camera(sphere);

		if (glfwGetKey(view.window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			u.update();
		}

		u.render();

		glfwSwapBuffers(view.window);

		glfwPollEvents();
	}

	view.cleanup();
	return 0;
}