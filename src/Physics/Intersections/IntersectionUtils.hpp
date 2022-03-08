#ifndef INTERSECTION_UTILS_H
#define INTERSECTION_UTILS_H

#include<list>
#include"Colliders/Utils/ShapeUtils.hpp"
#include"Colliders/MeshCollider/MeshHelpers.hpp"

// SAT
typedef struct Interval {
	float min;
	float max;
} Interval;

// Projects the shape onto an axis and returns an interval
Interval GetInterval(AABB& aabb, glm::vec3 axis); // AABB
Interval GetInterval(OBB& obb, glm::vec3 axis); // OBB
Interval GetInterval(Triangle& tri, glm::vec3 axis); // Triangle

// Checks if is overlaping on an axis
bool OverlapOnAxis(AABB& aabb, OBB& obb, glm::vec3 axis); // AABB vs OBB
bool OverlapOnAxis(OBB& obb1, OBB& obb2, glm::vec3 axis); // OBB vs OBB
bool OverlapOnAxis(AABB& aabb, Triangle& tri, glm::vec3 axis); // AABB vs Triangle
bool OverlapOnAxis(OBB& obb, Triangle& tri, glm::vec3 axis); // OBB vs Triangle
bool OverlapOnAxis(Triangle& tri1, Triangle& tri2, glm::vec3 axis); // Triangle vs Triangle

// Handles the edge case of triangle sides being paralleland 
// producing a cross product with zero length by testing analternate perpendicular axis
glm::vec3 SatCrossEdge(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);

// Returns the barycentric coordinates of a point with respect to a triangle
glm::vec3 Barycentric(glm::vec3 point, Triangle& tri);

#endif