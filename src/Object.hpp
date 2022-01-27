#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include<string>
#include<vector>

#include"Mesh.hpp"

// Object, allows to combine collider with texture
class Object {
public:
	// Empty shader and mesh
	Shader emptyShader;
	Mesh emptyMesh;

	// Object type (model/collider/both)
	std::string type = "both";

	// Shaders
	Shader& modelShader = emptyShader;
	Shader& colliderShader = emptyShader;
	// Meshes
	Mesh& modelMesh = emptyMesh;
	Mesh& colliderMesh = emptyMesh;
	// Object position
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	// Object model
	glm::mat4 model = glm::mat4(1.0f);

	// Object constructors
	Object() {}; // Empty
	Object(Shader& shader, Mesh& mesh, std::string type); // Only 1
	Object(Shader& textureShader, Mesh& mesh, Shader& colliderShader, Mesh& collider); // Both

	// Moves the Object to the specified coordinates
	void Move(glm::vec3 coordinates);
	// Sets Object's color
	void Color(glm::vec4 color, const GLchar* uniform);
	// Creates object in the main while loop
	void Instantiate(Camera& camera);
};

#endif