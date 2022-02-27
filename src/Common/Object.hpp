#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include<string>
#include<vector>

#include"../Graphics/Model.hpp"
#include"../Physics/PhysicsWorld.hpp"

class Object {
	public:
		// Shaders
		Shader& modelShader = emptyShader;
		// Model and collider
		Model& model = emptyModel;
		// The location of the Collider and Model relative to the center of the Object
		glm::vec3 modelPosition = glm::vec3(0.0f, 0.0f, 0.0f);

		Rigidbody& rigidbody = emptyRigidbody;

		// Object position
		glm::vec3 position = glm::vec3(0.0f);
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		glm::vec3 scale = glm::vec3(1.0f);
		GLfloat mass = rigidbody.mass;


		// Object constructors
		Object() {}; // Empty
		Object(Shader& shader, Model& objectModel)
			: model(objectModel), modelShader(shader) {};  // Only Model
		Object(Shader& shader, Model& objectModel, Rigidbody& objectRigidbody)
			: model(objectModel), modelShader(shader), rigidbody(objectRigidbody) {}; // Model with Rigidbody

		// Applies force to the object
		void ApplyForce(glm::vec3 force); 
		// Creates object in the main while loop
		void Instantiate(Camera& camera);
	private:
		// Empty shader, mesh and model
		Shader emptyShader;
		Model emptyModel;
		Rigidbody emptyRigidbody;
};

#endif