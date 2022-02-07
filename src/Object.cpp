#include"Object.hpp"

// Object with only Model
Object::Object(Shader& shader, Model& objectModel)
	: model(objectModel), modelShader(shader) {}

// Object with only Model
Object::Object(Shader& shader, Model& objectModel, Rigidbody& objectRigidbody)
	: model(objectModel), modelShader(shader), rigidbody(objectRigidbody) {}

void Object::ApplyForce(glm::vec3 f) {
	rigidbody.ApplyForce(f);
}

void Object::Instantiate(Camera& camera) {
	position = rigidbody.position;
	model.position = position + modelPosition;
	model.Draw(modelShader, camera);
}