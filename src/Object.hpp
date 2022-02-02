#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include<string>
#include<vector>

#include"Model.hpp"

// Object, allows to combine collider with texture
class Object {
	public:
		// Shaders
		Shader& modelShader = emptyShader;
		Shader& colliderShader = emptyShader;
		// Model and collider
		Model& model = emptyModel;
		Mesh& colliderMesh = emptyMesh;
		// Object position
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		// The location of the Collider and Model relative to the center of the Object
		glm::vec3 colliderPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);

		// Object constructors
		Object() {}; // Empty
		Object(Shader& shader, Model& objectModel); // Only model
		Object(Shader& shader, Mesh& colliderMesh); // Only collider
		Object(Shader& textureShader, Model& objectModel, Shader& cShader, Mesh& collider); // Both

		// Moves the Object in a specified direction with a specified speed
		void Move(glm::vec3 direction, GLfloat speed); 
		// Creates object in the main while loop
		void Instantiate(Camera& camera);
	private:
		std::string type = "both";

		// Empty shader, mesh and model
		Shader emptyShader;
		Mesh emptyMesh;
		Model emptyModel;
};

#endif