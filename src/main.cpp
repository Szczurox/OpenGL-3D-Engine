#include"Common/Object.hpp"
#include"Physics/PhysicsWorld.hpp"
#include"Physics/Intersections/ShapeIntersections.hpp"
#include"Physics/Intersections/LineIntersections.hpp"

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
void test();
void intersection_tests();
void ray_tests();
void line_tests();

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
	// Enables the Stencil Buffer
	glEnable(GL_STENCIL_TEST);
	// Sets rules for outcomes of stecil tests
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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

	Model model("res/Models/sword/scene.gltf");
	Rigidbody body(glm::vec3(0.0f), 1.0f);
	Object object(shaderProgram, model, body);

	object.modelPosition = glm::vec3(0.0f, 1.0f, 0.0f);
	object.position = glm::vec3(0.0f);
	object.rotation = glm::angleAxis(glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	object.scale = glm::vec3(0.009f);
	object.mass = 2.0f;

	// Camera
	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 2.0f, 2.0f));

	PhysicsWorld world;

	world.AddObject(&body);

	// variables for calcualting delta time
	float prvTime = 0.0f;
	float curTime = 0.0f;
	float dt;
	unsigned int counter = 0;

	test();

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		// FPS counter and calcualting delta time
		curTime = glfwGetTime();
		dt = curTime - prvTime;
		counter++;
		// Setting current title to the new title with new FPS value
		std::string FPS = std::to_string((1.0 / dt) * counter);
		std::string ms = std::to_string((dt / counter) * 1000);
		std::string title = "OpenGL - FPS: " + FPS + " / ms: " + ms;
		glfwSetWindowTitle(window, title.c_str());
		counter = 0;
		prvTime = curTime;
		// Background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clear the back buffer, depth buffer, stencil buffer and assign the new color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Get user inputs and adjust camera 
		camera.Inputs(window, dt);
		// Updates camera
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		floor.Draw(shaderProgram, camera);
		world.Step(dt);

		// Make it so the stencil test always passes
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		// Enable modifying of the stencil buffer
		glStencilMask(0xFF);
		object.Instantiate(camera);

		// Enable modifying of the stencil buffer
		glStencilMask(0xFF);
		// Clear stencil buffer
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		// Enable the depth buffer
		glEnable(GL_DEPTH_TEST);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// GLFW events
		glfwPollEvents();
	}

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


Sphere sphere1(glm::vec3(0.0f), 1.0f);
Sphere sphere2(glm::vec3(4.0f), 3.0f);
Sphere sphere3(glm::vec3(0.0f, -1.0f, 0.0f), 1.0f);

AABB aabb1(glm::vec3(0.0f), glm::vec3(2.0f));
AABB aabb2(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(2.0f));
AABB aabb3(glm::vec3(1.0f), glm::vec3(5.0f));
AABB aabb4(glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(1.0f));

OBB obb1;
OBB obb2(glm::vec3(0.0f, -3.1f, 0.0f), glm::vec3(1.0f), glm::mat3({ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }));
OBB obb3(glm::vec3(3.2f), glm::vec3(2.0f));

Triangle tri1(glm::vec3(-2.0f, -1.0f, 0.0f), glm::vec3(-3.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
Triangle tri2(glm::vec3(2.0f, 1.0f, 0.0f), glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
Triangle tri3(glm::vec3(-2.0f, -1.0f, 0.0f), glm::vec3(-4.0f, 0.0f, 1.0f), glm::vec3(-2.0f, 0.0f, 1.0f));

void test() {
	intersection_tests();
	ray_tests();
	line_tests();
	MeshCollider mesh;
	std::cout << CheckIntersection<AABB&>(mesh, aabb1) << std::endl;
}

void intersection_tests() {
	std::cout << "Intersection tests: \n\n"; 
	std::cout << "sphere1 vs sphere2: " << CheckIntersection<Sphere&, Sphere&>(sphere1, sphere2) << std::endl;
	std::cout << "sphere1 vs sphere3: " << CheckIntersection<Sphere&, Sphere&>(sphere1, sphere3) << std::endl << std::endl;

	std::cout << "aabb1 vs aabb2: " << CheckIntersection<AABB&, AABB&>(aabb1, aabb2) << std::endl;
	std::cout << "aabb1 vs aabb3: " << CheckIntersection<AABB&, AABB&>(aabb1, aabb3) << std::endl;
	std::cout << "aabb1 vs aabb4: " << CheckIntersection<AABB&, AABB&>(aabb2, aabb4) << std::endl << std::endl;

	std::cout << "aabb1 vs obb1: " << CheckIntersection<AABB&, OBB&>(aabb1, obb1) << std::endl;
	std::cout << "aabb1 vs obb2: " << CheckIntersection<AABB&, OBB&>(aabb1, obb2) << std::endl;
	std::cout << "aabb1 vs obb3: " << CheckIntersection<AABB&, OBB&>(aabb1, obb3) << std::endl << std::endl;

	std::cout << "obb1 vs obb2: " << CheckIntersection<OBB&, OBB&>(obb1, obb2) << std::endl;
	std::cout << "obb1 vs obb3: " << CheckIntersection<OBB&, OBB&>(obb1, obb3) << std::endl << std::endl;

	std::cout << "tri1 vs tri2: " << CheckIntersection<Triangle&, Triangle&>(tri1, tri2) << std::endl;
	std::cout << "tri1 vs tri3: " << CheckIntersection<Triangle&, Triangle&>(tri1, tri3) << std::endl;
	std::cout << "tri2 vs tri3: " << CheckIntersection<Triangle&, Triangle&>(tri2, tri3) << std::endl << std::endl << std::endl;
}

void ray_tests() {
	std::cout << "Ray tests: \n\n";
	Ray ray1(glm::vec3(0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	std::cout << "ray1 vs sphere1: " << Raycast(sphere1, ray1) << std::endl;
	std::cout << "ray1 vs sphere2: " << Raycast(sphere2, ray1) << std::endl;
	std::cout << "ray1 vs sphere3: " << Raycast(sphere3, ray1) << std::endl << std::endl;

	std::cout << "ray1 vs aabb1: " << Raycast(aabb1, ray1) << std::endl;
	std::cout << "ray1 vs aabb2: " << Raycast(aabb2, ray1) << std::endl;
	std::cout << "ray1 vs aabb3: " << Raycast(aabb3, ray1) << std::endl;
	std::cout << "ray1 vs aabb4: " << Raycast(aabb4, ray1) << std::endl << std::endl;

	std::cout << "ray1 vs obb1: " << Raycast(obb1, ray1) << std::endl;
	std::cout << "ray1 vs obb2: " << Raycast(obb2, ray1) << std::endl;
	std::cout << "ray1 vs obb3: " << Raycast(obb3, ray1) << std::endl << std::endl << std::endl;
}

void line_tests() {
	std::cout << "Line tests: \n\n";
	Line line1(glm::vec3(0.0f), glm::vec3(0.0f, -11.0f, 0.0f));
	std::cout << "line1 vs sphere1: " << Linetest(sphere1, line1) << std::endl;
	std::cout << "line1 vs sphere2: " << Linetest(sphere2, line1) << std::endl;
	std::cout << "line1 vs sphere3: " << Linetest(sphere3, line1) << std::endl << std::endl;

	std::cout << "line1 vs aabb1: " << Linetest(aabb1, line1) << std::endl;
	std::cout << "line1 vs aabb2: " << Linetest(aabb2, line1) << std::endl;
	std::cout << "line1 vs aabb3: " << Linetest(aabb3, line1) << std::endl;
	std::cout << "line1 vs aabb4: " << Linetest(aabb4, line1) << std::endl << std::endl;

	std::cout << "line1 vs obb1: " << Linetest(obb1, line1) << std::endl;
	std::cout << "line1 vs obb2: " << Linetest(obb2, line1) << std::endl;
	std::cout << "line1 vs obb3: " << Linetest(obb3, line1) << std::endl << std::endl << std::endl;
}