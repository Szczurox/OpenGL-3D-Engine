#ifndef SHAPE_UTILS_H
#define SHAPE_UTILS_H

#include"../Sphere.hpp"
#include"../Triangle.hpp"
#include"../Plane.hpp"
#include"../AABB.hpp"
#include"../Line.hpp"
#include"../OBB.hpp"
#include"../Ray.hpp"

// Performs epsilon tests
#define ET(x, y) \
	(fabsf((x)-(y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

// Squares vector
#define MagnitudeSq(x) \
	(glm::dot(x, x))

// Returns positive number if the point is in front of the plain,
// negative number if the point is behind the plane or
// 0 if the point is on the plane
float PlaneEquation(glm::vec3 pt, Plane& pl);
// Length of a line
float Length(Line& line);
// Squared length of a line
float LengthSq(Line& line);
// Decomposes a vector into parallel and perpendicular components with respect to another vector
glm::vec3 Project(glm::vec3 length, glm::vec3 direction);
// Creates Plane from Triangle
Plane PlaneFromTriangle(Triangle& triangle);
// Creates AABB from min and max
AABB AABBFromMinMax(glm::vec3 min, glm::vec3 max);
// Creates ray from 2 points
Ray RayFromPoints(glm::vec3 from, glm::vec3 to);
// Creates ray from a line
Ray RayFromLine(Line& line);

#endif