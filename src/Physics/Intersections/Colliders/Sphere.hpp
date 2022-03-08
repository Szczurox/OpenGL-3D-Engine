#ifndef SPHERE_STRUCT_H
#define SPHERE_STRUCT_H

#include<glm/glm.hpp>
#include"Collider.hpp"

class Sphere : public Collider {
public:
	glm::vec3 position;
	float radius;
	
	// Constructors
	Sphere() : radius(1.0f), position(0.0f) { type = ColliderType::SPHERE; } // Empty
	Sphere(const glm::vec3 p, float r) : position(p), radius(r) { type = ColliderType::SPHERE; } // From position and radius
};

#endif