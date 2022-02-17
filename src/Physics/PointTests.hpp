#ifndef POINT_TESTS_H
#define POINT_TESTS_H

#include"../Shapes/OBB.hpp"
#include"../Shapes/Sphere.hpp"
#include"../Shapes/Plane.hpp"
#include"../Shapes/Line.hpp"
#include"../Shapes/Ray.hpp"

// Performs epsilon tests
#define ET(x, y) \
	(fabsf((x)-(y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

// Sphere
bool PointInSphere(glm::vec3 point, Sphere& sphere);
glm::vec3 ClosestPoint(Sphere& sphere, glm::vec3 point);
// AABB
bool PointInAABB(glm::vec3 point, AABB& aabb);
glm::vec3 ClosestPoint(AABB& aabb, glm::vec3 point);
// OBB
bool PointInOBB(glm::vec3 point, OBB& obb);
glm::vec3 ClosestPoint(OBB& obb, glm::vec3 point);
// Plane
bool PointOnPlane(glm::vec3 point, Plane& plane);
glm::vec3 ClosestPoint(Plane& plane, glm::vec3 point);
// Line
bool PointOnLine(glm::vec3 point, Line& line);
glm::vec3 ClosestPoint(Line& line, glm::vec3 point);
// Ray
bool PointOnRay(glm::vec3 point, Ray& ray);
glm::vec3 ClosestPoint(Ray& ray, glm::vec3 point);

#endif