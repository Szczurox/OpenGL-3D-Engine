#include"Object.hpp"
#include"Physics/PhysicsWorld.hpp"
#include"Physics/Collisions/BoundingSphere.hpp"
#include"Physics/Collisions/AABB.hpp"

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
void collision_test();

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

	Model bunnyModel("res/Models/bunny/scene.gltf");
	Rigidbody body(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	Object bunny(shaderProgram, bunnyModel, body);

	// Camera
	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	PhysicsWorld World;

	World.AddObject(&body);

	// variables for calcualting delta time
	double prvTime = 0.0;
	double curTime = 0.0;
	GLfloat dt;
	unsigned int counter = 0;

	collision_test();

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
		bunny.ApplyForce(glm::vec3(0.1f, 0.0f, 0.0f));
		World.Step(dt);
		bunny.Instantiate(camera);

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


// Tests for collisions
void collision_test() {
	std::cout << "Collision Tests" << std::endl << std::endl;

	// Sphere - Sphere
	BoundingSphere sphere1(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);
	BoundingSphere sphere2(glm::vec3(0.0f, 3.0f, 0.0f), 1.0f);
	BoundingSphere sphere3(glm::vec3(0.0f, 0.0f, 2.0f), 1.0f);
	BoundingSphere sphere4(glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);

	IntersectData sphere1IntersectSphere2 = sphere1.IntersectBoundingSphere(sphere2);
	IntersectData sphere1IntersectSphere3 = sphere1.IntersectBoundingSphere(sphere3);
	IntersectData sphere1IntersectSphere4 = sphere1.IntersectBoundingSphere(sphere4);

	std::cout	<< "Sphere1 intersect Sphere2: " << sphere1IntersectSphere2.isIntersecting
				<< ", Distance: " << sphere1IntersectSphere2.distance << std::endl;
	std::cout	<< "Sphere1 intersect Sphere3: " << sphere1IntersectSphere3.isIntersecting
				<< ", Distance: " << sphere1IntersectSphere3.distance << std::endl;
	std::cout	<< "Sphere1 intersect Sphere4: " << sphere1IntersectSphere4.isIntersecting
				<< ", Distance: " << sphere1IntersectSphere4.distance << std::endl;

	std::cout << std::endl;
	
	// AABB - AABB
	AABB aabb1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	AABB aabb2(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
	AABB aabb3(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(2.0f, 1.0f, 1.0f));
	AABB aabb4(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, -1.0f));
	AABB aabb5(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.5f, 1.0f));

	IntersectData aabb1Intersectaabb2 = aabb1.IntersectAABB(aabb2);
	IntersectData aabb1Intersectaabb3 = aabb1.IntersectAABB(aabb3);
	IntersectData aabb1Intersectaabb4 = aabb1.IntersectAABB(aabb4);
	IntersectData aabb1Intersectaabb5 = aabb1.IntersectAABB(aabb5);

	std::cout	<< "AABB1 intersect AABB2: " << aabb1Intersectaabb2.isIntersecting
				<< ", Distance: " << aabb1Intersectaabb2.distance << std::endl;
	std::cout	<< "AABB1 intersect AABB3: " << aabb1Intersectaabb3.isIntersecting
				<< ", Distance: " << aabb1Intersectaabb3.distance << std::endl;
	std::cout	<< "AABB1 intersect AABB4: " << aabb1Intersectaabb4.isIntersecting
				<< ", Distance: " << aabb1Intersectaabb4.distance << std::endl;
	std::cout	<< "AABB1 intersect AABB5: " << aabb1Intersectaabb5.isIntersecting
				<< ", Distance: " << aabb1Intersectaabb5.distance << std::endl;

	std::cout << std::endl;
}