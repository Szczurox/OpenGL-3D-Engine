#include"PointTests.hpp"

// Sphere
// Checks if point is inside the sphere
bool CheckPoint(glm::vec3 point, Sphere& sphere) {
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
bool CheckPoint(glm::vec3 point, AABB& aabb) {
	// Get max and min point of the AABB
	glm::vec3 min = GetMin(aabb);
	glm::vec3 max = GetMax(aabb);

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
	glm::vec3 min = GetMin(aabb);
	glm::vec3 max = GetMax(aabb);

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
bool CheckPoint(glm::vec3 point, OBB& obb) {
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
		if (distance > obb.size[i] || distance < -obb.size[i])
			return false;
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
		if (distance > obb.size[i]) 
			distance = obb.size[i];

		if (distance < -obb.size[i]) 
			distance = -obb.size[i];
		// Adjust the final point by the axis and the current projected distance
		result += axis * distance;
	}
	return result;
}

// Plane
// Checks if point is on the Plane
bool CheckPoint(glm::vec3 point, Plane& plane) {
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
bool CheckPoint(glm::vec3 point, Line& line) {
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
bool CheckPoint(glm::vec3 point, Ray& ray) {
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
glm::vec3 ClosestPoint(Ray& ray, glm::vec3 point) {
	// The point projected onto the ray
	float t = glm::dot(point - ray.origin, ray.direction);
	// Clamp t point to positive direction
	t = fmaxf(t, 0.0f);
	return glm::vec3(ray.origin + ray.direction * t);
}

// Triangle
// Checks if point is intersected by the triangle
bool CheckPoint(glm::vec3 point, Triangle& triangle) {
	// Temporary triangle size of the original triangle with the local coordinate system of the point
	glm::vec3 a = triangle.a - point; // A
	glm::vec3 b = triangle.b - point; // B
	glm::vec3 c = triangle.c - point; // C
	// Normal of sides of the pyramid created using the point (P) and the temporary triangle (ABC)
	glm::vec3 nPBC = glm::cross(b, c); // P + B + C
	glm::vec3 nPCA = glm::cross(c, a); // P + C + A
	glm::vec3 nPAB = glm::cross(a, b); // P + A + B
	// If the faces of the pyramid do not have the same normal, the point is not in the triangle
	if (glm::dot(nPBC, nPCA) < 0.0f || glm::dot(nPBC, nPAB) < 0.0f)
		return false;
	// If all faces of the pyramid have the same normal, the pyramid is flat
	// That means the point is in the triangle
	return true;
}

// Returns closest point on the Triangle to a given point
glm::vec3 ClosestPoint(Triangle& triangle, glm::vec3 point) {
	Plane plane = PlaneFromTriangle(triangle);
	glm::vec3 closest = ClosestPoint(plane, point);
	if (CheckPoint(closest, triangle)) 
		return closest;
	// Closest point to the each side of the triangle
	Line ab(triangle.a, triangle.b); // AB
	Line bc(triangle.b, triangle.c); // BC
	Line ca(triangle.c, triangle.a); // CA
	glm::vec3 c1 = ClosestPoint(ab, point);
	glm::vec3 c2 = ClosestPoint(bc, point);
	glm::vec3 c3 = ClosestPoint(ca, point);
	// Measure how far each of the closest points are from the test point
	float magSq1 = MagnitudeSq(point - c1);
	float magSq2 = MagnitudeSq(point - c2);
	float magSq3 = MagnitudeSq(point - c3);
	// Return closest of the closest points
	if (magSq1 < magSq2 && magSq1 < magSq3) 
		return c1;
	else if (magSq2 < magSq1 && magSq2 < magSq3)
		return c2;
	return c3;
}