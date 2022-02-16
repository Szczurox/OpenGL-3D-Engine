#include"AABB.hpp"

glm::vec3 AABB::GetMin() {
	glm::vec3 p1 = position + size;
	glm::vec3 p2 = position - size;

	return glm::vec3(fminf(p1.x, p2.x), 
					 fminf(p1.y, p2.y), 
					 fminf(p1.z, p2.z));
}

glm::vec3 AABB::GetMax() {
	glm::vec3 p1 = position + size;
	glm::vec3 p2 = position - size;

	return glm::vec3(fmaxf(p1.x, p2.x),
					 fmaxf(p1.y, p2.y),
					 fmaxf(p1.z, p2.z));
}