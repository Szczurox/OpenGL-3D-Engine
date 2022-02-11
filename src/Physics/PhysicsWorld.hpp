#ifndef PHYSICS_WORLD_CLASS_H
#define PHYSICS_WORLD_CLASS_H

#include"Rigidbody.hpp"
#include<iostream>
#include<vector>

class PhysicsWorld {
	public:
		// Adds Rigidbody to Physics World
		void AddObject(Rigidbody* body);
		// Removes Rigidbody from Physics World
		void RemoveObject(Rigidbody* body);
		// Updates all Physics World objects
		void Step(GLfloat dt);
		// Constructor
		PhysicsWorld() {};
	
	private:
		// Vector with all Rigidbodies
		std::vector<Rigidbody*> rigidbodies;
		GLfloat gravity = -0.0981f;
};

#endif