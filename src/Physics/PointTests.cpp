#include"../Shapes/OBB.hpp"
#include"../Shapes/Sphere.hpp"

// Checks if point is inside the sphere
bool PointInSphere(glm::vec3 point, Sphere& sphere) {
	// Square magnitude of the line between the sphere center and the point
	float magSq = glm::dot(point - sphere.position, point - sphere.position);
	// Square radius of the sphere
	float radSq = sphere.radius * sphere.radius;

	// If square magnitude is smaller than the square radius, the point is inside the sphere
	return magSq < radSq;
}

// Returns closest point on the surface of the sphere to a given point
glm::vec3 ClosestPoint(Sphere& sphere, glm::vec3 point) {
	// Normalized vector from the center of the sphere to the point
	glm::vec3 sphereToPoint = glm::normalize(point - sphere.position);
	// The vector resized to the size of the radius
	sphereToPoint = sphereToPoint * sphere.radius;
	// The resized vector offset by the position of the sphere
	return sphereToPoint + sphere.position;
}

// Checks if point is inside the AABB
bool PointInAABB(glm::vec3 point, AABB& aabb) {
	// Get max and min point of the AABB
	glm::vec3 min = aabb.GetMin();
	glm::vec3 max = aabb.GetMax();

	// Not intersecting if any component of the point is smaller than 
	// the respective component of the min point of the AABB
	if (point.x < min.x || point.y < min.y || point.z < min.z)
		return false;
	// Not intersecting if any component of the point is larger than 
	// the respective component of the max point of the AABB
	if (point.x > max.x || point.y > max.y || point.z > max.z)
		return false;

	return true;
}

// Returns closest point on the surface of the AABB to a given point
glm::vec3 ClosestPoint(AABB& aabb, glm::vec3 point) {
	glm::vec3 result = point;
	// Get max and min point of the AABB
	glm::vec3 min = aabb.GetMin();
	glm::vec3 max = aabb.GetMax();

	// Point is clamped to make sure that it will never 
	// be smaller than min point or greater than max point
	
	// Clamp the closest point to the min point of the AABB
	result.x = (result.x < min.x) ? min.x : result.x;
	result.y = (result.y < min.x) ? min.y : result.y;
	result.z = (result.z < min.x) ? min.z : result.z;
	// Clamp the closest point to the max point of the AABB
	result.x = (result.x > max.x) ? max.x : result.x;
	result.y = (result.y > max.x) ? max.y : result.y;
	result.z = (result.z > max.x) ? max.z : result.z;

	return result;
}

// Checks if point is inside the OBB
bool PointInOBB(glm::vec3 point, OBB& obb) {
	// Point moved relative to the oriented bounding box
	glm::vec3 dir = point - obb.position;
	// Project the point onto each of the local axes of the box and 
	// compare the distance to the extent of the box on that axis
	for (int i = 0; i < 3; ++i) {
		// Vectors that represent axis being tested
		glm::vec3 orientation = obb.orientation[i * 3];
		glm::vec3 axis(orientation[1], orientation[1], orientation[2]);
		// Project the relative point onto that axis and 
		// record how far from the orgin of the box the projection is
		float distance = glm::dot(dir, axis);
		// The point is not inside the box if the distance greater than the extent of the box, 
		// or less than the negative extent of the box
		if (distance > obb.size[i]) {
			return false;
		}
		if (distance < -obb.size[i]) {
			return false;
		}
	}
	return true;
}