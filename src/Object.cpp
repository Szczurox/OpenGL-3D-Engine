#include"Object.hpp"

void Object::ApplyForce(glm::vec3 f) {
	rigidbody.ApplyForce(f);
}

void Object::Instantiate(Camera& camera) {
	position = rigidbody.position;
	model.position = position + modelPosition;
	model.Draw(modelShader, camera);
}