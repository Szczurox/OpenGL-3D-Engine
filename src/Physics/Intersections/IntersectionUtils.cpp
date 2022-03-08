#include"IntersectionUtils.hpp"

// Projects AABB onto an axis and returns an interval
Interval GetInterval(AABB& aabb, glm::vec3 axis) {
	// Get min and max points of AABB
	glm::vec3 n = GetMin(aabb); 
	glm::vec3 x = GetMax(aabb);
	// Vertices of AABB
	glm::vec3 vertices[8] = {
		glm::vec3(n.x, x.y, x.z),
		glm::vec3(n.x, x.y, n.z),
		glm::vec3(n.x, n.y, x.z),
		glm::vec3(n.x, n.y, n.z),
		glm::vec3(x.x, x.y, x.z),
		glm::vec3(x.x, x.y, n.z),
		glm::vec3(x.x, n.y, x.z),
		glm::vec3(x.x, n.y, n.z)
	};
	Interval result;
	result.min = result.max = glm::dot(axis, vertices[0]);
	// Project each vertex onto the provided axes
	for (int i = 1; i < 8; i++) {
		float projection = glm::dot(axis, vertices[i]);
		result.min = (projection < result.min) ? projection : result.min;
		result.max = (projection > result.max) ? projection : result.max;
	}
	return result;
}

// Projects OBB onto an axis and returns an interval
Interval GetInterval(OBB& obb, glm::vec3 axis) {
	// OBB center
	glm::vec3 c = obb.position;
	// OBB extents
	glm::vec3 e = obb.size;
	// OBB orientation
	glm::mat3 o = obb.orientation;
	// OBB axis
	glm::vec3 a[3] = {
		glm::vec3(o[0].x, o[0].y, o[0].z),
		glm::vec3(o[1].x, o[1].y, o[1].z),
		glm::vec3(o[2].x, o[2].y, o[2].z),
	};
	// OBB vertices
	glm::vec3 vertices[8] = {
		c + a[0] * e[0] + a[1] * e[1] + a[2] * e[2],
		c - a[0] * e[0] + a[1] * e[1] + a[2] * e[2],
		c + a[0] * e[0] - a[1] * e[1] + a[2] * e[2],
		c + a[0] * e[0] + a[1] * e[1] - a[2] * e[2],
		c - a[0] * e[0] - a[1] * e[1] - a[2] * e[2],
		c + a[0] * e[0] - a[1] * e[1] - a[2] * e[2],
		c - a[0] * e[0] + a[1] * e[1] - a[2] * e[2],
		c - a[0] * e[0] - a[1] * e[1] + a[2] * e[2]
	};
	Interval result;
	result.min = result.max = glm::dot(axis, vertices[0]);
	// Project each vertex onto the provided axes
	for (int i = 1; i < 8; i++) {
		float projection = glm::dot(axis, vertices[i]);
		result.min = (projection < result.min) ? projection : result.min;
		result.max = (projection > result.max) ? projection : result.max;
	}

	return result;
}

// Projects Triangle onto an axis and returns an interval
Interval GetInterval(Triangle& tri, glm::vec3 axis) {
	Interval result;
	// Project the first point of the triangle onto the axis and 
	// store it as the min and max of the interval
	result.min = glm::dot(axis, *tri.points[0]);
	result.max = result.min;
	// Project the remaining two points of the triangle onto the axis
	for (int i = 1; i < 3; ++i) {
		// Project point onto the axis
		float value = glm::dot(axis, *tri.points[i]);
		// If the projected point is less than min store it as the min of the interval
		result.min = fminf(result.min, value);
		// If the projected point is greater than max store it as the max of the interval
		result.max = fmaxf(result.max, value);
	}
	// Return interval
	return result;
}

// Checks if is overlaping on an axis
// AABB vs OBB
bool OverlapOnAxis(AABB& aabb, OBB& obb, glm::vec3 axis) {
	// Get 2 intervals
	Interval a = GetInterval(aabb, axis);
	Interval b = GetInterval(obb, axis);
	// Check if they are overlaping
	return ((b.min <= a.max) && (a.min <= b.max));
}

// OBB vs OBB
bool OverlapOnAxis(OBB& obb1, OBB& obb2, glm::vec3 axis) {
	// Get 2 intervals
	Interval a = GetInterval(obb1, axis);
	Interval b = GetInterval(obb2, axis);
	// Check if they are overlaping
	return ((b.min <= a.max) && (a.min <= b.max));
}

// AABB vs Triangle
bool OverlapOnAxis(AABB& aabb, Triangle& tri, glm::vec3 axis) {
	// Get 2 intervals
	Interval a = GetInterval(aabb, axis);
	Interval b = GetInterval(tri, axis);
	// Check if they are overlaping
	return ((b.min <= a.max) && (a.min <= b.max));
}

// OBB vs Triangle
bool OverlapOnAxis(OBB& obb, Triangle& tri, glm::vec3 axis) {
	Interval a = GetInterval(obb, axis);
	Interval b = GetInterval(tri, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

// Triangle vs Triangle
bool OverlapOnAxis(Triangle& tri1, Triangle& tri2, glm::vec3 axis) {
	Interval a = GetInterval(tri1, axis);
	Interval b = GetInterval(tri2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

// Handles the edge case of triangle sides being paralleland 
// producing a cross product with zero length by testing analternate perpendicular axis
glm::vec3 SatCrossEdge(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {
	// The default sides
	glm::vec3 ab = a - b;
	glm::vec3 cd = c - d;
	// Cross product of the sides
	glm::vec3 result = glm::cross(ab, cd);
	// If the magnitude of the cross product is not 0, the sides are not parallel
	if (!ET(MagnitudeSq(result), 0))
		return result;
	else {
		// Temporary axis perpendicular to AB
		glm::vec3 axis = glm::cross(ab, c - a);
		result = glm::cross(ab, axis);
		// If the magnitude of the new cross product is not zero, 
		// the perpendicular axis produced valid results
		if (!ET(MagnitudeSq(result), 0))
			return result;
		// If the magnitude of the cross product was zero, both triangles are coplanar and 
		// there is no way to get a proper cross product out of them
		return glm::vec3(0.0f);
	}
}

// Returns the barycentric coordinates of a point with respect to a triangle
glm::vec3 Barycentric(glm::vec3 point, Triangle& tri) {
	// Vectors from the test point to each point of the triangle
	glm::vec3 ap = point - tri.a;
	glm::vec3 bp = point - tri.b;
	glm::vec3 cp = point - tri.c;
	// Edges of the triangle
	glm::vec3 ab = tri.b - tri.a;
	glm::vec3 ac = tri.c - tri.a;
	glm::vec3 bc = tri.c - tri.b;
	glm::vec3 cb = tri.b - tri.c;
	glm::vec3 ca = tri.a - tri.c;
	// Vector perpendicular to edge AB
	glm::vec3 v = ab - Project(ab, cb);
	// Point projected onto v vector
	float a = 1.0f - (glm::dot(v, ap) / glm::dot(v, ab));
	// Vector perpendicular to edge BC
	v = bc - Project(bc, ac);
	// Point projected onto v vector
	float b = 1.0f - (glm::dot(v, bp) / glm::dot(v, bc));
	// Vector perpendicular to edge CA
	v = ca - Project(ca, ab);
	// Point projected onto v vector
	float c = 1.0f - (glm::dot(v, cp) / glm::dot(v, ca));

	return glm::vec3(a, b, c);
}
