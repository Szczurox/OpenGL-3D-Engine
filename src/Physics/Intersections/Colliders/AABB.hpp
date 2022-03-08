#ifndef AABB_CLASS_H
#define AABB_CLASS_H

#include<glm/glm.hpp>
#include"Collider.hpp"

class AABB : public Collider {
public:
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 size = glm::vec3(1.0f);

	// Constructors
	AABB() { type = ColliderType::AABB; } // Empty
	AABB(glm::vec3 pos, glm::vec3 s) : position(pos), size(s) { type = ColliderType::AABB; } // From position and size
};

#endif 