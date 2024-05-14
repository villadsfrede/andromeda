#include "Camera.h"

void Camera::uniform(Shader& shader)
{
	// view and perspective identity matrices
	glm::mat4 view = glm::mat4(1);
	glm::mat4 perspective = glm::mat4(1);

	// generate view and perspective
	view = glm::lookAt(position, position + orientation, up);
	perspective = glm::perspective(angle, aspect, near, far);

	// export view, perspective and angle to shader as uniforms
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "perspective"), 1, GL_FALSE, glm::value_ptr(perspective));
	glUniform1fv(glGetUniformLocation(shader.shaderProgram, "angle"), 1, &angle);
}

void Camera::input(GLFWwindow* window)
{
	// [w] -> forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * orientation;
	}
	// [a] -> left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	// [s] -> backwards
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * -orientation;
	}
	// [d] -> right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	// [L-shift] change orientation
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		// Hide cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// mouse coordinates
		double mouseX;
		double mouseY;

		// current width and height of viewport
		int width;
		int height;

		// mouse and viewport coordinates
		glfwGetCursorPos(window, &mouseX, &mouseY);
		glfwGetWindowSize(window, &width, &height);

		// Calculate rotation of x and y
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Calculate new orientation
		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

		// Check if orientation is valid
		if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}

		orientation = glm::rotate(orientation, glm::radians(-rotY), up);

		// Set cursor to center of screen
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	// Release [L-shift] stop changing orientation
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		// Show cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

// Constructor
Camera::Camera(float angle, float aspect, float near, float far)
{
	Camera::angle = angle;
	Camera::aspect = aspect;
	Camera::near = near;
	Camera::far = far;
}
