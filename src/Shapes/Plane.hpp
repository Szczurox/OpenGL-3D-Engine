#ifndef PLANE_CLASS_H
#define PLANE_CLASS_H

#include<glm/glm.hpp>

class Plane {
public:
	glm::vec3 normal;
	float distance;

	// Constructors
	Plane() : normal(1.0f, 0.0f, 0.0f), distance(0.0f) {}; // Empty
	Plane(const glm::vec3 n, float d) : normal(n), distance(d) {}; // From normal and distance

	float PlaneEquation(const glm::vec3 &pt);
};

#endif