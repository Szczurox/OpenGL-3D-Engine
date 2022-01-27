#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"shaderClass.hpp"
#include"VAO.hpp"
#include"VBO.hpp"
#include"EBO.hpp"
#include"Texture.hpp"
#include"Camera.hpp"
#include"Game.hpp"
#include"resourceManager.hpp"

// Vertices coordinates of a object1
GLfloat vertices[] =
{ //     COORDINATES     |        COLORS          |    TexCoord   |        NORMALS       //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices of a object1 for vertices order 
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

// Vertices coordinates of a cube
GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const unsigned int windowWidth = 800;
const unsigned int windowHeight = 800;

Game Test(windowWidth, windowHeight);

int main() {
	// Initialize GLFW
	glfwInit();

	// Hint GLFW the version and the profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
	GLFWwindow* window = glfwCreateWindow(windowHeight, windowHeight, "OpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Key callback handling
	glfwSetKeyCallback(window, key_callback);

	// Load Glad
	gladLoadGL();

	// Viewport of OpenGL in the Window
	glViewport(0, 0, windowWidth, windowHeight);

	// Creates Shader Object using vertices shader and fragment shader
	Shader shaderProgram = ResourceManager::LoadShader("res/Shaders/default.vert", "res/Shaders/default.frag", "shaderProgram");

	// Vertex Array Object
	VAO VAO1;
	VAO1.Bind();

	// Vertex Buffer Object linked to veritces
	VBO VBO1(vertices, sizeof(vertices));
	// Element Buffer Object  linked to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes to VAO 
	// Step between vertices
	GLsizeiptr stride = 11 * sizeof(float);
	// Coordinates
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, stride, (void*)0);
	// Colors
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
	// Texture coordinates
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float)));
	// Normals
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, stride, (void*)(8 * sizeof(float)));

	// Unbind all objects to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// Shader for the Cube
	Shader lightShader = ResourceManager::LoadShader("res/Shaders/light.vert", "res/Shaders/light.frag", "lightShader");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all objects to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Sets Cube and object1 position
	glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 object1Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 object1Model = glm::mat4(1.0f);
	object1Model = glm::translate(object1Model, object1Pos);


	lightShader.Activate();
	// Exports the Cube Model matrix to the Fragment Shader
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	// Exports the Cube Light Color to the Fragment Shader
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	shaderProgram.Activate();
	// Exports the object1 Model matrix to the Fragment Shader
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(object1Model));
	// Exports the object1 Light Color to the Fragment Shader
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	// Exports the object1 Light Position to the Fragment Shader for lighting
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	// Gets ID of uniform "scale"
	GLuint scaleUni = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture

	// Generates texture
	Texture planksTex("res/Textures/planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	planksTex.texUnit(shaderProgram, "tex0", 0);
	Texture planksSpec("res/Textures/planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	planksSpec.texUnit(shaderProgram, "tex1", 1);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Camera
	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// Background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear the back buffer, depth buffer and assign the new color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Get user inputs and adjust camera
		camera.Inputs(window);
		// Updates camera
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Tell OpenGL which Shader Program to use
		shaderProgram.Activate();

		// Exports the Camera Position to the Fragment Shader for specular lighting
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Exports camera matrix to the Vertex Shader of the object1
		camera.Matrix(shaderProgram, "camMatrix");

		// Bind texture to make it appear in rendering
		planksTex.Bind();
		// Bind specular map
		planksSpec.Bind();
		// Bind the VAO to tell OpenGL to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Tells OpenGL which Shader Program we want to use
		lightShader.Activate();


		// Some test stuff
		//object1Pos = glm::vec3(0.0f, 0.0f, 0.0f);
		//object1Model = glm::mat4(1.0f);
		//object1Model = glm::rotate(object1Model, glm::radians(x), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		//glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(object1Model));
		//lightPos = glm::vec3(0.5f, x, 0.5f);
		//lightModel = glm::mat4(1.0f);
		//lightModel = glm::translate(lightModel, lightPos);
		//glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
		//x += 0.5f;


		// Export the camera matrix to the Vertex Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// GLFW events
		glfwPollEvents();
	}

	// Delete objects
	planksSpec.Delete();
	planksTex.Delete();
	VBO1.Delete();
	VAO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Destroys window and terminates GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}  

// Key callback handling
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// On ESC key press close the window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	// Give key input info to the Game Class
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Test.Keys[key] = true;
		else if (action == GLFW_RELEASE)
			Test.Keys[key] = false;
	}
}