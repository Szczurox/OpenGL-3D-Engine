#ifndef AABB_CLASS_H
#define AABB_CLASS_H

#include<glm/glm.hpp>

class AABB {
public:
	glm::vec3 position;
	glm::vec3 size;

	// Constructors
	AABB() : position(0.0f), size(1.0f) {} // Empty
	AABB(glm::vec3 pos, glm::vec3 s) : position(pos), size(s) {} // From position and size

	// Minimum point of AABB
	glm::vec3 GetMin();
	// Maximum point of AABB
	glm::vec3 GetMax();
};

#endif 