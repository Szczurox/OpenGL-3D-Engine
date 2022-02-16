#ifndef AABB_CLASS_H
#define AABB_CLASS_H

#include<glm/glm.hpp>

class AABB {
public:
	glm::vec3 position;
	glm::vec3 size;

	// Constructors
	AABB() : position(0.0f), size(1.0f) {} // Empty
	AABB(const glm::vec3 o, const glm::vec3 s) : position(o), size(s) {} // From position and size
	AABB(const glm::vec3 min, const glm::vec3 max) :
		position((min + max) * 0.5f), size((max - min) * 0.5f) {}; // From min and max

	// Minimum point of AABB
	glm::vec3 GetMin();
	// Maximum point of AABB
	glm::vec3 GetMax();
};

#endif 