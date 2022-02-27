#ifndef SHAPE_INTERSECTION_H
#define SHAPE_INTERSECTION_H

#include"PointTests.hpp"

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
// Triangle vs Sphere
bool CheckIntersection(Triangle& tri , Sphere& sphere);
inline bool CheckIntersection(Sphere& sphere, Triangle& tri);
// Triangle vs AABB
bool CheckIntersection(Triangle& tri, AABB& aabb);
inline bool CheckIntersection(AABB& aabb, Triangle& tri);
// Triangle vs OBB
bool CheckIntersection(Triangle& tri, OBB& obb);
inline bool CheckIntersection(OBB& obb, Triangle& tri);
// Triangle vs Plane
bool CheckIntersection(Triangle& tri, Plane& plane);
inline bool CheckIntersection(Plane& plane, Triangle& tri);
// Triangle vs Triangle
bool CheckIntersection(Triangle& tri1, Triangle& tri2);

#endif