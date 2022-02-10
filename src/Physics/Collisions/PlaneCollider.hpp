#ifndef PLANE_COLLIDER_CLASS_H
#define PLANE_COLLIDER_CLASS_H

#include"IntersectData.hpp"
#include"BoundingSphere.hpp"
#include"AABB.hpp"

class PlaneCollider {
public:
	glm::vec3 normal;
	float distance;

	// Constructor
	PlaneCollider(glm::vec3 normal, float distance) : normal(normal), distance(distance) {};

	// Normalizes plane
	PlaneCollider Normalized();
	// Plane Collider vs Bounding Sphere collision detection
	IntersectData CheckIntersection(BoundingSphere& other);
	IntersectData CheckIntersection(AABB& other);
};

#endif
