#include"Rigidbody.hpp"

void Rigidbody::ApplyForce(glm::vec3 f) {
	force += f;
}

void Rigidbody::ApplyGravity(GLfloat g) {
	ApplyForce(mass * glm::vec3(0.0f, g, 0.0f));
}

void Rigidbody::Step(GLfloat dt) {
	// Changes the acceleration by given forces
	velocity += force / mass * dt;
	// Changes the position
	position += velocity * dt;
	// Resets net force
	force = glm::vec3(0.0f);
}
