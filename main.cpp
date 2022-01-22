#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


GLfloat vertices[] = {
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Right
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Left
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Top
	-0.5f / 2 , 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner left
	0.5f / 2 , 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // Inner down
};

GLuint indices[] = {
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1, // Upper triangle
};


int main() {
	// Initialize GLFW
	glfwInit();

	// Hint GLFW the version and the profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Load Glad
	gladLoadGL();

	glViewport(0, 0, 800, 800);

	// Creates Shader Object using vertices shader and fragment shader
	Shader shaderProgram("default.vert", "default.frag");

	// Vertex Array Object
	VAO VAO1;
	VAO1.Bind();

	// Vertex Buffer Object linked to veritces
	VBO VBO1(vertices, sizeof(vertices));
	// Element Buffer Object  linked to indices
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);

	// Unbind all objects
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// Background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear the back buffer and assign the new color
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program to use
		shaderProgram.Activate();
		// Bind the VAO to tell OpenGL to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// GLFW events
		glfwPollEvents();
	}

	// Delete objects
	VBO1.Delete();
	VAO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Destroys window and terminates GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}  