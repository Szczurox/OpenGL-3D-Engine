#ifndef OBB_CLASS_H
#define OBB_CLASS_H

#include"AABB.hpp"

class OBB {
public:
	glm::vec3 position;
	glm::vec3 size;
	glm::mat3 orientation;

	// Constructors
	OBB() : position(0.0f), size(1.0f), orientation(1.0f) {} // Empty
	OBB(const glm::vec3 o, const glm::vec3 s) 
		: position(o), size(s), orientation(0.0f) {} // From position and size
	OBB(AABB& aabb) 
		: position(aabb.position), size(aabb.size), orientation(0.0f) {} // From AABB
	OBB(const glm::vec3 p, const glm::vec3 s, const glm::mat3 o)
		: position(p), size(s), orientation(o) {}; // From position, size and orientation
};

#endif
