#include"Object.hpp"

// Vertices coordinates of a pyramid
Vertex vertices[] =
{ //         COORDINATES				 |            COLORS          |          TexCoord          |         NORMALS       //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices of a pyramid for vertices order 
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

// Vertices coordinates of a cube
Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
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


// window dimensions
const unsigned int windowWidth = 800;
const unsigned int windowHeight = 800;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

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
	glfwSetKeyCallback(window, key_callback);

	// Load Glad
	gladLoadGL();

	// Viewport of OpenGL in the Window
	glViewport(0, 0, windowWidth, windowHeight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Floor textures
	Texture textures[]{
		Texture("res/Textures/planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("res/Textures/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE),
	};

	// Creates Shader Object using vertices shader and fragment shader
	Shader shaderProgram("res/Shaders/default.vert", "res/Shaders/default.frag");

	// Floor vertices, indices and textures
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	// Floor mesh
	Mesh floor(verts, inds, tex);

	// Shader for the Light Cube
	Shader lightShader("res/Shaders/light.vert", "res/Shaders/light.frag");

	// Light Cube vertices, indices and textures
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInds(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Light Cube Mesh
	Mesh light(lightVerts, lightInds, tex);
	Mesh cube(lightVerts, lightInds, tex);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Sets Cube and Pyramid position
	glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	lightShader.Activate();
	// Exports the Cube Model matrix to the Fragment Shader
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	// Exports the Cube Light Color to the Fragment Shader
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

<<<<<<< HEAD
=======
	cubeShader.Activate();
	// Exports the Cube Model matrix to the Fragment Shader
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	// Exports the Cube Light Color to the Fragment Shader
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

>>>>>>> parent of 73c726d (Revert "Objects")
	shaderProgram.Activate();
	// Exports the Pyramid Model matrix to the Fragment Shader
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	// Exports the Pyramid Light Color to the Fragment Shader
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	// Exports the Pyramid Light Position to the Fragment Shader for lighting
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	// Objects
	Mesh cube(lightVerts, lightInds, tex);
	Shader cubeShader("res/Shaders/light.vert", "res/Shaders/light.frag");
	Object Cube(cubeShader, cube, "model");
	Cube.Color(glm::vec4(1.0f, 1.0f, 1.0f, 0.3f), "lightColor");
	Cube.Move(glm::vec3(0.0f, 0.1f, 0.0f));


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

		floor.Draw(shaderProgram, camera);
<<<<<<< HEAD
		light.Draw(lightShader, camera);
		Cube.Instantiate(camera);
=======
		cube.Draw(cubeShader, camera);
>>>>>>> parent of 73c726d (Revert "Objects")

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// GLFW events
		glfwPollEvents();
	}

	// Delete objects
	lightShader.Delete();
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
}