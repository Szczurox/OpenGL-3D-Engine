#ifndef BOUNDING_SPHERE_CLASS_H
#define BOUNDING_SPHERE_CLASS_H

#include"IntersectData.hpp"

class BoundingSphere {
public:
	glm::vec3 center;
	GLfloat radius;

	// Constructor
	BoundingSphere(glm::vec3 center, GLfloat radius) 
		: center(center), radius(radius) {}

	// Checks if is intersecting another Bounding Sphere
	IntersectData CheckIntersection(BoundingSphere& other);
};

#endif