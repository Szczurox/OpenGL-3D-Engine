#include"Camera.hpp"


// Camera constructor 
Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

// Updates camera
void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
	// Initializes View and Projection matrices
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	cameraMatrix = projection * view;
}

// Exports camera matrix to the Vertex Shader
void Camera::Matrix(Shader& shader, const char* uniform) {
	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window, float dt) {
	// WSAD movement (forward, backwards, left, right)
	speed *= dt;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Orientation;
	};
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed * -Orientation;
	};
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	};
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	};
	// Space to move up, left control to move down
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Position += speed * Up;
	};
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Position += speed * -Up;
	};
	// Shift to sprint
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = sprint;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = normalSpeed;
	};

	// Mouse button pressed (held down)
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping around on the first click
		if (firstClick) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Cursor coordinates
		double mouseX, mouseY;
		// Fetches cursor coordinates
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Shifts the cursor coordinates to place it in the center of the window and transforms the coordinates into degrees
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (height / 2)) / height;

		// Calculates new vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides if the new vertical Orientation is legal or not
		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f) or (glm::angle(newOrientation, -Up) <= glm::radians(5.0f))))) {
			Orientation = newOrientation;
		}

		// Rotates the Orientation
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	// Mouse button released
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		// Shows cursor becuase the camera is no longer used
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera is used it doesn't jump around
		firstClick = true;
	}
}