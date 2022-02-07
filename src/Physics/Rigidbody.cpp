#include"Rigidbody.hpp"
#include<iostream>

Rigidbody::Rigidbody(glm::vec3 pos, GLfloat m, glm::vec3 f, glm::vec3 v)
	:position(pos), mass(m), force(f), velocity(v) {}

void Rigidbody::ApplyForce(glm::vec3 f) {
	force += f;
}

void Rigidbody::Step(GLfloat dt) {
	velocity += force / mass * dt;
	position += velocity * dt;
	std::cout << velocity.y << ", " << mass << ", " << std::endl;
	force = glm::vec3(0.0f);
}