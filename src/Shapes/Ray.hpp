#ifndef RAY_CLASS_H
#define RAY_CLASS_H

#include<glm/glm.hpp>

class Ray {
public:
	glm::vec3 origin;
	glm::vec3 direction;

	// Constructors
	Ray() : direction(0.0f, 0.0f, 1.0f), origin(0.0f) {} // Empty
	Ray(const glm::vec3 o, const glm::vec3 d) 
		: origin(o), direction(glm::normalize(d)) {}; // From origin and direction
	Ray(const glm::vec3 from, const glm::vec3 to) 
		: origin(from), direction(glm::normalize(to - from)) {}; // From 2 points
};

#endif