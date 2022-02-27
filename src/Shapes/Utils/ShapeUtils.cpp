#include"ShapeUtils.hpp"

// Returns positive number if the point is in front of the plain,
// negative number if the point is behind the plane or
// 0 if the point is on the plane
float PlaneEquation(glm::vec3 pt, Plane& pl) {
	return glm::dot(pt, pl.normal) - pl.distance;
}

// Length of a line
float Length(Line& line) {
	return glm::length(line.start - line.end);
}

// Squared length of a line
float LengthSq(Line& line) {
	return MagnitudeSq(line.start - line.end);
}

// Decomposes a vector into parallel and perpendicular components with respect to another vector
glm::vec3 Project(glm::vec3 length, glm::vec3 direction) {
	return direction * (glm::dot(length, direction) / MagnitudeSq(direction));
}

// Creates Plane from Triangle
Plane PlaneFromTriangle(Triangle& tri) {
	Plane plane;
	plane.normal = glm::normalize(glm::cross(tri.b - tri.a, tri.c - tri.a));
	plane.distance = glm::dot(plane.normal, tri.a);
	return plane;
}

// Creates AABB from min and max
AABB AABBFromMinMax(glm::vec3 min, glm::vec3 max) {
	return AABB((min + max) * 0.5f, (max - min) * 0.5f);
}

// Creates ray from 2 points
Ray RayFromPoints(glm::vec3 from, glm::vec3 to) {
	return Ray(from, glm::normalize(to - from));
}

// Creates ray from a line
Ray RayFromLine(Line& line) {
	return RayFromPoints(line.start, line.end);
}