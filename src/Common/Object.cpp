#include"Object.hpp"

void Object::ApplyForce(glm::vec3 f) {
	rigidbody.ApplyForce(f);
}

void Object::Instantiate(Camera& camera) {
	// Sets model properties
	position = rigidbody.position;
	model.position = position + modelPosition;
	model.transformScale = scale;
	model.transformRotation = rotation;
	// Sets rigidbody properties
	rigidbody.mass = mass;
	// Draws model
	model.Draw(modelShader, camera);
}