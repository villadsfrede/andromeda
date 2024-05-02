#include "Camera.h"

void Camera::operator () (Shader& shader)
{
	glm::mat4 view = glm::mat4(1);
	glm::mat4 perspective = glm::mat4(1);

	view = glm::lookAt(position, position + orientation, up);
	//view = glm::lookAt(position, glm::vec3(0,0,0), up);
	perspective = glm::perspective(angle, aspect, near, far);

	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "perspective"), 1, GL_FALSE, glm::value_ptr(perspective));
	glUniform1fv(glGetUniformLocation(shader.shaderProgram, "angle"), 1, &angle);
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
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		double mouseX;
		double mouseY;

		int width;
		int height;

		glfwGetCursorPos(window, &mouseX, &mouseY);
		glfwGetWindowSize(window, &width, &height);

		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

		if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}

		orientation = glm::rotate(orientation, glm::radians(-rotY), up);

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

Camera::Camera(float angle, float aspect, float near, float far)
{
	Camera::angle = angle;
	Camera::aspect = aspect;
	Camera::near = near;
	Camera::far = far;
}
