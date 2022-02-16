#ifndef SPHERE_STRUCT_H
#define SPHERE_STRUCT_H

#include<glm/glm.hpp>

class Sphere {
public:
	glm::vec3 position;
	float radius;
	
	// Constructors
	Sphere() : radius(1.0f), position(0.0f) {} // Empty
	Sphere(const glm::vec3 p, float r) : position(p), radius(r) {} // From position and radius
};

#endif