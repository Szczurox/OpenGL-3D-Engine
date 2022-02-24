#ifndef LINE_INTERSECTIONS_H
#define LINE_INTERSECTIONS_H

#include"PointTests.hpp"

// Raycasting (checks if a ray intersects a shape)
float Raycast(Sphere& sphere, Ray& ray); // Raycast Sphere
float Raycast(AABB& aabb, Ray& ray); // Raycast AABB
float Raycast(OBB& obb, Ray& ray); // Raycast OBB
float Raycast(Plane& plane, Ray& ray); // Raycast Plane

#endif