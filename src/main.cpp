#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


GLfloat vertices[] = {
	//    COORDINATES      |         COLORS         //
	-0.5f, -0.5f,  0.0f,		1.0f, 0.0f, 0.0f,   // Bottom left
	-0.5f,  0.5f,  0.0f,		0.0f, 1.0f, 0.0f,   // Top left
	 0.5f,  0.5f,  0.0f,		0.0f, 0.0f, 1.0f,   // Top right
	 0.5f, -0.5f,  0.0f,		1.0f, 1.0f, 1.0f,   // Bottom right
};

GLuint indices[] = {
	0, 2, 1, // Upper triangle
	0, 3, 2, // Lower triangle
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

	// Links VBO attributes (coordinates, colors) to VAO 
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all objects
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// Background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear the back buffer and assign the new color
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program to use
		shaderProgram.Activate();
		// Assigns a value to the uniform
		glUniform1f(uniID, 0.5f);
		// Bind the VAO to tell OpenGL to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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