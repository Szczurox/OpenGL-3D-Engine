#include"PlaneCollider.hpp"

// Normalizes plane
PlaneCollider PlaneCollider::Normalized() {
	float magnitude = glm::length(normal);
	return PlaneCollider(normal / magnitude, distance / magnitude);
};

IntersectData PlaneCollider::CheckIntersection(BoundingSphere& other) {
	// How far along the Plane Collider's normal the Bounding Sphere center is
	float distanceFromSphereCenter = fabs(glm::dot(normal, other.center) - distance);
	// Distance from Bounding Sphere to Plane Collider
	float distanceFromSphere = distanceFromSphereCenter - other.radius;

	return IntersectData {
		distanceFromSphere < 0,
		distanceFromSphere
	};
};

IntersectData PlaneCollider::CheckIntersection(AABB& other) {
	// AABB extents vector
	glm::vec3 aabbExtents = (other.maxExtents - other.minExtents) / 2.0f;
	// AABB center
	glm::vec3 center = other.minExtents + aabbExtents;
	// Dot Product between the Plane Collider normal and the center of the AABB
	float radius = fabs(glm::dot(glm::abs(normal), glm::abs(aabbExtents)));
	BoundingSphere sphere(center, radius);
	return CheckIntersection(sphere);
}