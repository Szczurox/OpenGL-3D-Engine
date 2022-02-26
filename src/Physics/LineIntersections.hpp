#ifndef LINE_INTERSECTIONS_H
#define LINE_INTERSECTIONS_H

#include"PointTests.hpp"

// Raycasting 
// Checks if a ray intersects a shape and 
// returns the distance from the ray origin to the shape surface
float Raycast(Sphere& sphere, Ray& ray); // Raycast Sphere
float Raycast(AABB& aabb, Ray& ray); // Raycast AABB
float Raycast(OBB& obb, Ray& ray); // Raycast OBB
float Raycast(Plane& plane, Ray& ray); // Raycast Plane

// Linetest 
// Checks if a line intersects a shape, returns boolean value
bool Linetest(Sphere& sphere, Line& line); // Linetest Sphere
bool Linetest(AABB& aabb, Line& line); // Linetest AABB
bool Linetest(OBB& obb, Line& line); // Linetest OBB
bool Linetest(Plane& plane, Line& line); // Linetest Plane

#endif