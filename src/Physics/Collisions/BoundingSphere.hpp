#ifndef BOUNDING_SPHERE_CLASS_H
#define BOUNDING_SPHERE_CLASS_H

#include"IntersectData.hpp"
#include<math.h>

class BoundingSphere {
public:
	glm::vec3 center;
	GLfloat radius;

	// Constructor
	BoundingSphere(glm::vec3 center, GLfloat radius) 
		: center(center), radius(radius) {}

	// Checks if is intersecting another Bounding Sphere
	IntersectData IntersectBoundingSphere(BoundingSphere& other);
};

#endif