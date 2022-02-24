#ifndef SHAPE_INTERSECTION_H
#define SHAPE_INTERSECTION_H

#include"PointTests.hpp"

// SAT
typedef struct Interval {
	float min;
	float max;
} Interval;

// Projects the shape onto an axis and returns an interval
Interval GetInterval(AABB& aabb, glm::vec3 axis);
Interval GetInterval(OBB& obb, glm::vec3 axis);

// Checks if is overlaping on an axis
bool OverlapOnAxis(AABB& aabb, OBB& obb, glm::vec3 axis);
bool OverlapOnAxis(OBB& obb1, OBB& obb2, glm::vec3 axis);

// Sphere vs Sphere
bool CheckIntersection(Sphere& s1, Sphere& s2);
// Sphere vs AABB
bool CheckIntersection(Sphere& sphere, AABB& aabb);
inline bool CheckIntersection(AABB& aabb, Sphere& sphere);
// Sphere vs OBB
bool CheckIntersection(Sphere& sphere, OBB& obb);
inline bool CheckIntersection(OBB& obb, Sphere& sphere);
// Sphere vs Plane
bool CheckIntersection(Sphere& sphere, Plane& plane);
inline bool CheckIntersection(Plane& plane, Sphere& sphere);
// AABB vs AABB
bool CheckIntersection(AABB& a, AABB& b);
// AABB vs OBB
bool CheckIntersection(AABB& aabb, OBB& obb);
inline bool CheckIntersection(OBB& obb, AABB& aabb);
// AABB vs Plane
bool CheckIntersection(AABB& aabb, Plane& plane);
inline bool CheckIntersection(Plane& plane, AABB& aabb);
// OBB vs OBB
bool CheckIntersection(OBB& obb1, OBB& obb2);
// OBB vs Plane
bool CheckIntersection(OBB& obb, Plane& plane);
inline bool CheckIntersection(Plane& plane, OBB& obb);
// Plane vs Plane
bool CheckIntersection(Plane& p1, Plane& p2);

#endif