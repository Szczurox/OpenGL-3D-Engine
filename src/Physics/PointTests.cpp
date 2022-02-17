#include"PointTests.hpp"

// Sphere
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

// AABB
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

// OBB
// Checks if point is inside the OBB
bool PointInOBB(glm::vec3 point, OBB& obb) {
	// Point moved relative to the oriented bounding box
	glm::vec3 dir = point - obb.position;
	// Project the point onto each of the local axes of the box and 
	// compare the distance to the extent of the box on that axis
	for (int i = 0; i < 3; i++) {
		// Vectors that represent axis being tested
		glm::vec3 orientation = obb.orientation[i * 3];
		glm::vec3 axis(orientation[1], orientation[1], orientation[2]);
		// Project the relative point onto that axis and 
		// record how far from the orgin of the box the projection is
		float distance = glm::dot(dir, axis);
		// The point is not inside the box if the distance is greater than the extent of the box, 
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

// Returns closest point on the surface of the OBB to a given point
glm::vec3 ClosestPoint(OBB& obb, glm::vec3 point) {
	glm::vec3 result = obb.position;
	glm::vec3 dir = point - obb.position;
	// Project the point onto each of the local axes of the box and 
	// compare the distance to the extent of the box on that axis
	for (int i = 0; i < 3; i++) {
		// Vectors that represent axis being tested
		glm::vec3 orientation = obb.orientation[i * 3];
		glm::vec3 axis(orientation[1], orientation[1], orientation[2]);
		// Project the relative point onto that axis
		float distance = glm::dot(dir, axis);
		// Clamp component on axis if needed
		if (distance > obb.size[i]) {
			distance = obb.size[i];
		}
		if (distance < -obb.size[i]) {
			distance = -obb.size[i];
		}
		// Adjust the final point by the axis and the current projected distance
		result = result + (axis * distance);
	}
	return result;
}

// Plane
// Checks if point is on the Plane
bool PointOnPlane(glm::vec3 point, Plane& plane) {
	// By subtracting the distance of the plane from the distance of the point, 
	// we can check if a point is on the plane
	float dot = glm::dot(point, plane.normal);
	return ET(dot - plane.distance, 0.0f);
}

// Returns closest point on the Plane to a given point
glm::vec3 ClosestPoint(Plane& plane, glm::vec3 point) {
	float dot = glm::dot(plane.normal, point);
	float distance = dot - plane.distance;
	// Subtracts the plane normal scaled by the signed distance from the original point
	return point - plane.normal * distance;
}

// Line
// Checks if point is on the line
bool PointOnLine(glm::vec3 point, Line& line) {
	// Closest point on the segment to the tested point
	glm::vec3 closest = ClosestPoint(line, point);
	float distanceSq = glm::dot(closest - point, closest - point);
	return ET(distanceSq, 0.0f);
}
// Returns closest point on the Line to a given point
glm::vec3 ClosestPoint(Line& line, glm::vec3 point) {
	// Line Vector
	glm::vec3 lVec = line.end - line.start;
	// How far along the line the point is
	float t = glm::dot(point - line.start, lVec) / glm::dot(lVec, lVec);
	// Because t is normalized, a value of less than 0 or 
	// greater than 1 falls outside of the line segment
	t = fmaxf(t, 0.0f); // Clamp to 0
	t = fminf(t, 1.0f); // Clamp to 1
	return line.start + lVec * t;
}

// Ray
// Checks if point is intersected by the ray
bool PointOnRay(glm::vec3 point, Ray& ray) {
	// If the point is the origin of the ray we can return true early
	if (point == ray.origin)
		return true;
	// Normal from the tested point to the ray origin
	glm::vec3 normal = glm::normalize(point - ray.origin);
	// If both vectors point in the same direction, 
	// their dot product should be 1
	float diff = glm::dot(normal, ray.direction);
	return ET(diff, 1.0f);
}

// Returns closest point on the Ray to a given point
glm::vec3 ClosestPoint( Ray& ray, glm::vec3 point) {
	// The point projected onto the ray
	float t = glm::dot(point - ray.origin, ray.direction);
	// Clamp t point to positive direction
	t = fmaxf(t, 0.0f);
	return glm::vec3(ray.origin + ray.direction * t);
}