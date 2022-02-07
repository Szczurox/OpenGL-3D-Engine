#ifndef RIGIDBODY_CLASS_H
#define RIGIDBODY_CLASS_H

#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

class Rigidbody {
	public:
		// Rigidbody 
		glm::vec3 position = glm::vec3(0.0f);
		glm::vec3 velocity = glm::vec3(0.0f);
		glm::vec3 force = glm::vec3(0.0f);
		GLfloat mass = 1.0f;

		Rigidbody() {};
		Rigidbody(glm::vec3 pos, GLfloat m = 1.0f, glm::vec3 f = glm::vec3(0.0f), glm::vec3 v = glm::vec3(0.0f)); 

		void ApplyForce(glm::vec3 f);

		void Step(GLfloat dt);
};

#endif