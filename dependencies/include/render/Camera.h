#ifndef ANDROMEDA_CAMERA_H
#define ANDROMEDA_CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Camera {
public:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 orientation = glm::vec3(0, 0, -1);
	glm::vec3 up = glm::vec3(0, 1, 0);

	float aspect;
	float angle;
	float near;
	float far;

	float speed = 1;
	float sensitivity = 1;

	void operator () (Shader& shader, const char* uniform);

	void input(GLFWwindow* window);

	Camera(float angle, float aspect, float near, float far);
};

#endif
