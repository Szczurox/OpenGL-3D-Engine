#include"AABB.hpp"

IntersectData AABB::CheckIntersection(AABB& other) {
	// Distances between AABBs on all axis
	glm::vec3 distance1 = other.minExtents - maxExtents;
	glm::vec3 distance2 = minExtents - other.maxExtents;
	// Gets largerst distance
	glm::vec3 distance = glm::max(distance1, distance2);
	float maxDistance = std::max(std::max(distance.x, distance.y), distance.z);

	return IntersectData{
		maxDistance < 0,
		maxDistance
	};
}