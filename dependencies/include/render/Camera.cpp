#include "Camera.h"

void Camera::operator () (Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1);
	glm::mat4 projection = glm::mat4(1);

	view = glm::lookAt(position, position + orientation, up);
	projection = glm::perspective(angle, aspect, near, far);

	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
}

Camera::Camera(float angle, float aspect, float near, float far)
{
	Camera::angle = angle;
	Camera::aspect = aspect;
	Camera::near = near;
	Camera::far = far;
}
