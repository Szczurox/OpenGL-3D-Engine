#ifndef AABB_CLASS_H
#define AABB_CLASS_H

#include"IntersectData.hpp"

class AABB {
	public:
		glm::vec3 minExtents;
		glm::vec3 maxExtents;

		AABB(glm::vec3 minExtents, glm::vec3 maxExtents)
			: minExtents(minExtents), maxExtents(maxExtents) {}

		IntersectData IntersectAABB(AABB& other);
};

#endif
