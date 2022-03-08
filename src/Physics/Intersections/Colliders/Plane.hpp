#ifndef PLANE_CLASS_H
#define PLANE_CLASS_H

#include<glm/glm.hpp>
#include"Collider.hpp"

class Plane : public Collider {
public:
	glm::vec3 normal;
	float distance;

	// Constructors
	Plane() : normal(1.0f, 0.0f, 0.0f), distance(0.0f) { type = ColliderType::PLANE;  }; // Empty
	Plane(const glm::vec3 n, float d) : normal(n), distance(d) { type = ColliderType::PLANE; }; // From normal and distance
};

#endif