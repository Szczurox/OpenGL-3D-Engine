#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.hpp"

class Camera {
	public:
		// Main three vectors used to find camera position and orientation
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		// Width and height of the window
		int width;
		int height;

		// Adjust camera speed and sensitivity
		float speed = 0.1f;
		float sensitivity = 100.0f;

		// Normal speed and sprint speed (while pressing shift)
		const float sprint = 0.1f;
		const float normalSpeed = 0.04f;

		// Prevents camera from jumping around when clicking the left click in the window for the first time
		bool firstClick = true;

		// Camera constructor
		Camera(int width, int height, glm::vec3 position);

		void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
		// Handles camera input
		void Inputs(GLFWwindow* window);
};

#endif