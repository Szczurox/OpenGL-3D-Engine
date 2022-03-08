#ifndef POINT_TESTS_H
#define POINT_TESTS_H

#include"IntersectionUtils.hpp"
#include<iostream>

// Sphere
bool CheckPoint(glm::vec3 point, Sphere& sphere);
glm::vec3 ClosestPoint(Sphere& sphere, glm::vec3 point);
// AABB
bool CheckPoint(glm::vec3 point, AABB& aabb);
glm::vec3 ClosestPoint(AABB& aabb, glm::vec3 point);
// OBB
bool CheckPoint(glm::vec3 point, OBB& obb);
glm::vec3 ClosestPoint(OBB& obb, glm::vec3 point);
// Plane
bool CheckPoint(glm::vec3 point, Plane& plane);
glm::vec3 ClosestPoint(Plane& plane, glm::vec3 point);
// Line
bool CheckPoint(glm::vec3 point, Line& line);
glm::vec3 ClosestPoint(Line& line, glm::vec3 point);
// Ray
bool CheckPoint(glm::vec3 point, Ray& ray);
glm::vec3 ClosestPoint(Ray& ray, glm::vec3 point);
// Triangle
bool CheckPoint(glm::vec3 point, Triangle& triangle);
glm::vec3 ClosestPoint(Triangle& triangle, glm::vec3 point);

#endif