#ifndef RIGIDBODY_CLASS_H
#define RIGIDBODY_CLASS_H

#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<iostream>

class Rigidbody {
	public:
		// Rigidbody 
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 velocity = glm::vec3(0.0f);
		// Sum of all forces acting on the body
		glm::vec3 force = glm::vec3(0.0f);
		GLfloat mass = 1.0f;

		// Constructors 
		Rigidbody() {}; // Empty (default values)
		Rigidbody(glm::vec3 pos, GLfloat m = 1.0f, glm::vec3 f = glm::vec3(0.0f), glm::vec3 v = glm::vec3(0.0f))
			: position(pos), mass(m), force(f), velocity(v) {};

		// Adds force
		void ApplyForce(glm::vec3 f);
		// Adds gravity force
		void ApplyGravity(GLfloat g);

		// Rigidbody update
		void Step(GLfloat dt);
};

#endif