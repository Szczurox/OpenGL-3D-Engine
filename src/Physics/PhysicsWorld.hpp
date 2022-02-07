#ifndef PHYSICS_WORLD_CLASS_H
#define PHYSICS_WORLD_CLASS_H

#include"Rigidbody.hpp"
#include<iostream>
#include<map>
#include<vector>

class PhysicsWorld {
	public:
		void AddObject(std::string name, Rigidbody* body);
		void RemoveObject(std::string name);
		void Step(GLfloat dt);
		PhysicsWorld() {};
	
	private:
		std::vector<Rigidbody*> m_objects;
		std::map<std::string, Rigidbody*> rigidbodies;
		glm::vec3 gravity = glm::vec3(0, 0.0981f, 0);
};

#endif