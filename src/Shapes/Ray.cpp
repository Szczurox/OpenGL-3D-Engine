#include"Ray.hpp"

// Creates ray from 2 points
Ray RayFromPoints(glm::vec3 from, glm::vec3 to) {
	return Ray(from, to - from);
}