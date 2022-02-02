#include"Object.hpp"

// Object with only Model
Object::Object(Shader& shader, Model& objectModel)
	: model(objectModel), type("model"), modelShader(shader) {}

// Object with only Collider
Object::Object(Shader& shader, Mesh& collider)
	: colliderMesh(collider), type("collider"), colliderShader(shader) {}

// Object with collider and model
Object::Object(Shader& shader, Model& model, Shader& cShader, Mesh& collider)
	: modelShader(shader), model(model), colliderMesh(collider), colliderShader(cShader) {}

// Moves the Object in a specified direction with a specified speed
void Object::Move(glm::vec3 direction, GLfloat speed) {
	glm::vec3 move = direction * speed;
	position += move;
}

void Object::Instantiate(Camera& camera) {
	// Renders object
	if (type == "model" || type == "both") {
		model.position = position + modelPosition;
		model.Draw(modelShader, camera);
	}
	if (type == "collider" || type == "both") {
		colliderMesh.Draw(colliderShader, camera, glm::mat4(1.0f), position + colliderPosition);
	}
}