#include"AABB.hpp"

IntersectData AABB::IntersectAABB(AABB& other) {
	glm::vec3 distances1 = other.minExtents - maxExtents;
	glm::vec3 distances2 = minExtents - other.maxExtents;
	glm::vec3 distances = glm::max(distances1, distances2);

	float maxDistance = distances.x;
	if (distances.y > maxDistance) maxDistance = distances.y;
	if (distances.z > maxDistance) maxDistance = distances.z;

	return IntersectData{
		maxDistance < 0,
		maxDistance
	};
}