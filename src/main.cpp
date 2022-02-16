#include"Object.hpp"
#include"Physics/PhysicsWorld.hpp"

// Vertices coordinates of a floor
Vertex vertices[] =
{  //           COORDINATES		    	 |            COLORS          |          TexCoord          |         NORMALS       //
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

// Vertices coordinates of a cuboid
Vertex cuboidVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.2f,  0.3f)},
	Vertex{glm::vec3(-0.1f, -0.2f, -0.3f)},
	Vertex{glm::vec3(0.1f, -0.2f, -0.3f)},
	Vertex{glm::vec3(0.1f, -0.2f,  0.3f)},
	Vertex{glm::vec3(-0.1f,  0.2f,  0.3f)},
	Vertex{glm::vec3(-0.1f,  0.2f, -0.3f)},
	Vertex{glm::vec3(0.1f,  0.2f, -0.3f)},
	Vertex{glm::vec3(0.1f,  0.2f,  0.3f)}
};

GLuint cuboidIndices[] =
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

	// Floor textures
	Texture textures[]{
		Texture("res/Textures/planks.png", "diffuse", 0),
		Texture("res/Textures/planksSpec.png", "specular", 1),
	};

	// Creates Shader Object using vertices shader and fragment shader
	Shader shaderProgram("res/Shaders/default.vert", "res/Shaders/default.frag");

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Floor vertices, indices and textures
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	// Floor mesh
	Mesh floor(verts, inds, tex);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Sets Cube and Pyramid position
	glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	shaderProgram.Activate();
	// Exports the Floor Model matrix to the Floor Fragment Shader
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	// Exports the Light Color to the Floor Fragment Shader
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	// Exports the Light Position to the Floor Fragment Shader for lighting
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Model model("res/Models/bunny/scene.gltf");
	Rigidbody body(glm::vec3(0.0f), 1.0f);
	Object object(shaderProgram, model, body);

	object.position = glm::vec3(0.0f);
	object.rotation = glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	object.scale = glm::vec3(0.5f);
	object.mass = 2.0f;

	// Camera
	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	PhysicsWorld world;

	world.AddObject(&body);

	// variables for calcualting delta time
	float prvTime = 0.0f;
	float curTime = 0.0f;
	GLfloat dt;
	unsigned int counter = 0;

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// FPS counter and calcualting delta time
		curTime = glfwGetTime();
		dt = curTime - prvTime;
		counter++;
		if (dt >= 1.0 / 30.0) {
			// Setting current title to the new title with new FPS value
			std::string FPS = std::to_string((1.0 / dt) * counter);
			std::string ms = std::to_string((dt / counter) * 1000);
			std::string title = "OpenGL - FPS: " + FPS + " / ms: " + ms;
			glfwSetWindowTitle(window, title.c_str());
			prvTime = curTime;
			counter = 0; 
		}
		// Background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear the back buffer, depth buffer and assign the new color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Get user inputs and adjust camera 
		camera.Inputs(window);
		// Updates camera
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		floor.Draw(shaderProgram, camera);
		object.ApplyForce(glm::vec3(0.0f, 0.0f, 0.1f));
		world.Step(dt);
		object.Instantiate(camera);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// GLFW events
		glfwPollEvents();
	}

	glDisable(GL_BLEND);

	// Delete objects
	shaderProgram.Delete();

	// Destroys window and terminates GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

// Key callback handling
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	// On ESC key press close the window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}