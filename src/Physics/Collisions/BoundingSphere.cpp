#include"BoundingSphere.hpp"

// Checks if is intersecting another Bounding Sphere
IntersectData BoundingSphere::CheckIntersection(BoundingSphere& other) {
	// Length of the sum of the radii of the two spheres
	float radiusDist = radius + other.radius;
	// Distans between the centers of two spheres
	float centerDist = glm::length(other.center - center);
	return IntersectData {  
		centerDist < radiusDist, // Is intersecting another Bounding Sphere
		centerDist - radiusDist  // Distance between 2 spheres
	};
}