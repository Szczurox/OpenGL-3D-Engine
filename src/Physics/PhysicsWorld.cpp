#include"PhysicsWorld.hpp"

void PhysicsWorld::AddObject(std::string name, Rigidbody* body) {
	rigidbodies[name] = body;
}

void PhysicsWorld::RemoveObject(std::string name) {
	rigidbodies.erase(name);
}

void PhysicsWorld::Step(GLfloat dt) {
	for (auto const& element : rigidbodies) {
		Rigidbody* obj = element.second;
		std::cout << element.first << ": " << obj->position.x << ", " << obj->position.y << ", " << obj->position.z << std::endl;
		obj->force += obj->mass * gravity; // apply a force

		obj->velocity += obj->force / obj->mass * dt;
		obj->position += obj->velocity * dt;
		obj->force = glm::vec3(0.0f); // reset net force at the end
	}
}