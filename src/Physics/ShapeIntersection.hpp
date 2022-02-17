#ifndef SHAPE_INTERSECTION_H
#define SHAPE_INTERSECTION_H

#include"PointTests.hpp"

// Squares vector
#define MagnitudeSq(x) \
	(glm::dot(x, x))

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

// SAT
typedef struct Interval {
	float min;
	float max;
} Interval;
Interval GetInterval(AABB& aabb, glm::vec3 axis);
Interval GetInterval(OBB& obb, glm::vec3 axis);
// Checks if is overlaping on an axis
bool OverlapOnAxis(AABB& aabb, OBB& obb, glm::vec3 axis);

// AABB vs OBB
bool CheckIntersection(AABB& aabb, OBB& obb);
inline bool CheckIntersection(OBB& obb, AABB& aabb);


#endif