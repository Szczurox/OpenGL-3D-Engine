#include"PhysicsWorld.hpp"

void PhysicsWorld::AddObject(Rigidbody* body) {
	rigidbodies.push_back(body);
}

void PhysicsWorld::RemoveObject(Rigidbody* body) {
	rigidbodies.erase(std::remove(rigidbodies.begin(), rigidbodies.end(), body), rigidbodies.end());
}

void PhysicsWorld::Step(GLfloat dt) {
	for (Rigidbody* obj : rigidbodies) {
		obj->ApplyGravity(gravity);
		obj->Step(dt);
	}
}