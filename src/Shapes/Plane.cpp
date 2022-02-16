#include"Plane.hpp"

float Plane::PlaneEquation(const glm::vec3& pt) {
	return glm::dot(pt, normal) - distance;
}