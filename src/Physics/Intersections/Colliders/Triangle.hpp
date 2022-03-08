#ifndef TRIANGLE_CLASS_H
#define TRIANGLE_CLASS_H

#include"Collider.hpp"
#include<glm/glm.hpp>

class Triangle : public Collider {
public:
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
	glm::vec3* points[3] = { &a, &b, &c };

	// Constructors
	Triangle() : a(0.0f), b(0.0f), c(0.0f) { type = ColliderType::TRIANGLE; } // Empty
	Triangle(const glm::vec3 p1, const glm::vec3 p2, const glm::vec3 p3)
		: a(p1), b(p2), c(p3) {
		type = ColliderType::TRIANGLE;
	} // From 3 points
};

#endif