#include "view.h"

bool View::init()
{
	if (!glfwInit())
	{
		return false;
	}

	// Set OpenGL context hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFW window
	window = glfwCreateWindow(WWIDTH, WHEIGHT, "ANDROMEDA", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return false;
	}

	// set GLFW context to window
	glfwMakeContextCurrent(window);

	// Load glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return false;
	}

	// Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Enable vertex shader to set point size
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	// Enable depth testing for 3D
	glEnable(GL_DEPTH_TEST);

	return true;
}

void View::renderUI()
{
	// Create new ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// View frame
	ImGui::Begin("View");
	// FPS counter
	ImGui::Text("FPS = %f", ImGui::GetIO().Framerate);
	// Backgroundcolor editorr
	ImGui::ColorEdit4("Background color", bg);
	
	// Change algorithm to direct-sum
	if (ImGui::Button("Direct-Sum"))
	{
		if (universe)
		{
			universe->algorithm = std::make_unique<DirectSum>(universe->body);
		}
	}

	// Change algorihtm to barnes-hut
	if (ImGui::Button("Barnes-Hut"))
	{
		if (universe)
		{
			universe->algorithm = std::make_unique<BarnesHut>(universe->body);
		}
	}
	ImGui::End();

	// Camera frame
	ImGui::Begin("Camera");
	// Show position, orientation and up
	ImGui::Text("Position = (%f, %f, %f)", camera->position.x, camera->position.y, camera->position.z);
	ImGui::Text("Orientation = (%f, %f, %f)", camera->orientation.x, camera->orientation.y, camera->orientation.z);
	ImGui::Text("Up = (%f, %f, %f)", camera->up.x, camera->up.y, camera->up.z);
	// Speed slider
	ImGui::SliderFloat("Speed", &camera->speed, 0.1f, 10.0f);
	// Sensitivity slider
	ImGui::SliderFloat("Sensitivity", &camera->sensitivity, 1.0f, 100.0f);
	ImGui::End();

	// Universe frame
	ImGui::Begin("Universe");
	// Parameter sliders
	ImGui::SliderInt("Objects", &objects, 1, 10000);
	ImGui::SliderFloat("Position minimum", &pmin, 10e9, 1000e9, "%.0f");
	ImGui::SliderFloat("Position maximum", &pmax, 1000e9, 10000e9, "%.0f");
	ImGui::SliderFloat("Velocity minimum", &vmin, 1e3, 50e3, "%.0f");
	ImGui::SliderFloat("Velocity maximum", &vmax, 50e3, 100e3, "%.0f");
	ImGui::SliderInt("Seed", &seed, 1, 100000);

	// Generate new universe
	if (ImGui::Button("Generate"))
	{
		universe = std::make_unique<Universe>(objects, mass, pmin, pmax, vmin, vmax, seed);
	}

	// File path input
	ImGui::InputText("File", file, 64);

	// Save current universe
	if (ImGui::Button("Save"))
	{
		universe->save(file);
	}

	// Load new universe into current
	if (ImGui::Button("Load"))
	{
		universe->load(file);
	}

	ImGui::End();

	// Render all ImGui elements
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void View::cleanup()
{
	// Free memory
	glfwDestroyWindow(window);
	glfwTerminate();
}