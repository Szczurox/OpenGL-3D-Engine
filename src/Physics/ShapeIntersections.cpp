#include"ShapeIntersection.hpp"

// Sphere vs Sphere intersection
bool CheckIntersection(Sphere& s1, Sphere& s2) {
	// Sum of the radius of the spheres
	float radSum = s1.radius + s2.radius;
	// Squared distance between two spheres
	float sqDist = MagnitudeSq(s1.position - s2.position);
	// Intersection occurs if the squared distance is less than the squared radii
	return sqDist < radSum* radSum;
}

// Sphere vs AABB intersection
bool CheckIntersection(Sphere& sphere, AABB& aabb) {
	// Closest point on the AABB to the center of the Sphere
	glm::vec3 closestPoint = ClosestPoint(aabb, sphere.position);
	// Squared distance between the closest point and the center of the Sphere
	float distSq = MagnitudeSq(sphere.position - closestPoint);
	// Squared radius of the Sphere
	float radSq = sphere.radius * sphere.radius;
	// Intersecting if the squared distance is less than the squared radius
	return distSq < radSq;
}

// AABB vs Sphere intersection
inline bool CheckIntersection(AABB& aabb, Sphere& sphere) {
	return CheckIntersection(sphere, aabb);
}

// Sphere vs OBB intersection
bool CheckIntersection(Sphere& sphere, OBB& obb) {
	// Works similarly to AABB intersection detection
	glm::vec3 closestPoint = ClosestPoint(obb, sphere.position);
	float distSq = MagnitudeSq(sphere.position - closestPoint);
	float radSq = sphere.radius * sphere.radius;
	return distSq < radSq;
}

// OBB vs Sphere intersection
inline bool CheckIntersection(OBB& obb, Sphere& sphere) {
	return CheckIntersection(sphere, obb);
}

// Sphere vs Plane intersection
bool CheckIntersection(Sphere& sphere, Plane& plane) {
	// Works similarly to AABB intersection detection
	glm::vec3 closestPoint = ClosestPoint(plane, sphere.position);
	float distSq = MagnitudeSq(sphere.position - closestPoint);
	float radiusSq = sphere.radius * sphere.radius;
	return distSq < radiusSq;
}

// Plane vs Sphere intersection
inline bool CheckIntersection(Plane& plane, Sphere& sphere) {
	return CheckIntersection(sphere, plane);
}

// AABB vs AABB intersection
bool CheckIntersection(AABB& a, AABB& b) {
	// Get the min and max points of both AABBs
	glm::vec3 aMin = a.GetMin();
	glm::vec3 aMax = a.GetMax();
	glm::vec3 bMin = b.GetMin();
	glm::vec3 bMax = b.GetMax();
	// Check for overlap with min and max points on all 3 axis
	return  (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
			(aMin.y <= bMax.y && aMax.y >= bMin.y) &&
			(aMin.z <= bMax.z && aMax.z >= bMin.z);
}


// SAT functions
Interval GetInterval(AABB& aabb, glm::vec3 axis) {
	// Get min and max points of AABB
	glm::vec3 n = aabb.GetMin();
	glm::vec3 x = aabb.GetMax();
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

// Checks if is overlaping on axis
bool OverlapOnAxis(AABB& aabb, OBB& obb, glm::vec3 axis) {
	Interval a = GetInterval(aabb, axis);
	Interval b = GetInterval(obb, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OverlapOnAxis(OBB& obb1, OBB& obb2, glm::vec3 axis) {
	Interval a = GetInterval(obb1, axis);
	Interval b = GetInterval(obb2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}


// AABB vs OBB intersection
bool CheckIntersection(AABB& aabb, OBB& obb) {
	// OBB orientation
	glm::mat3 o = obb.orientation;

	glm::vec3 axes[15] = {
		glm::vec3(1, 0, 0), // AABB axis 1
		glm::vec3(0, 1, 0), // AABB axis 2
		glm::vec3(0, 0, 1), // AABB axis 3
		glm::vec3(o[0].x, o[0].y, o[0].z), // OBB axis 1
		glm::vec3(o[1].x, o[1].y, o[1].z), // OBB axis 2
		glm::vec3(o[2].x, o[2].y, o[2].z), // OBB axis 3
	};

	// Get remaining axes
	for (int i = 0; i < 3; ++i) {
		axes[6 + i * 3 + 0] = glm::cross(axes[i], axes[0]);
		axes[6 + i * 3 + 1] = glm::cross(axes[i], axes[1]);
		axes[6 + i * 3 + 2] = glm::cross(axes[i], axes[2]);
	}

	// Looping through all 15 axes of separation to check if there is an overlap or not
	// Shape intersects if all 15 overlap
	for (int i = 0; i < 15; i++) {
		if (!OverlapOnAxis(aabb, obb, axes[i])) {
			// Separating axis found
			return false;
		}
	}
	// Seperating axis not found
	return true; 
}

// OBB vs AABB intersection
inline bool CheckIntersection(OBB& obb, AABB& aabb) {
	return CheckIntersection(aabb, obb);
}

// AABB vs Plane intersection
bool CheckIntersection(AABB& aabb, Plane& plane) {
	// Project half extemts of AABB onto the plane
	float pLen = aabb.size.x * fabsf(plane.normal.x) +
				 aabb.size.y * fabsf(plane.normal.y) +
				 aabb.size.z * fabsf(plane.normal.z);
	// Distance from the center of the AABB to the plane
	float dot = glm::dot(plane.normal, aabb.position);
	float dist = dot - plane.distance;
	// Intersection occurs if the distance falls within the projected side
	return fabsf(dist) <= pLen;
}

// Plane vs AABB intersection
inline bool CheckIntersection(Plane& plane, AABB& aabb) {
	return CheckIntersection(aabb, plane);
}

// OBB vs OBB intersection
bool CheckIntersection(OBB& obb1, OBB& obb2) {
	// OBBs orientation
	glm::mat3 o1 = obb1.orientation;
	glm::mat3 o2 = obb2.orientation;

	glm::vec3 axes[15] = {
		glm::vec3(o1[0].x, o1[0].y, o1[0].z),
		glm::vec3(o1[1].x, o1[1].y, o1[1].z),
		glm::vec3(o1[2].x, o1[2].y, o1[2].z),
		glm::vec3(o2[0].x, o2[0].y, o2[0].z),
		glm::vec3(o2[1].x, o2[1].y, o2[1].z),
		glm::vec3(o2[2].x, o2[2].y, o2[2].z)
	};
	// Get remaining axes
	for (int i = 0; i < 3; i++) { 
		axes[6 + i * 3 + 0] = glm::cross(axes[i], axes[0]);
		axes[6 + i * 3 + 1] = glm::cross(axes[i], axes[1]);
		axes[6 + i * 3 + 2] = glm::cross(axes[i], axes[2]);
	}

	// Checking if separatian axes overlap, if all overlap then the intersection occurs
	for (int i = 0; i < 15; i++) {
		if (!OverlapOnAxis(obb1, obb2, axes[i])) {
			// Separating axis found
			return false;
		}
	}
	// Separating axis not found
	return true;
}

// OBB vs Plane intersection
bool CheckIntersection(OBB& obb, Plane& plane) {
	// OBB orientation
	glm::mat3 o = obb.orientation;
	glm::vec3 normal = plane.normal;
	// Project half extemts of OBB onto the plane
	float pLen = obb.size.x * fabsf(glm::dot(normal, o[0])) +
				 obb.size.y * fabsf(glm::dot(normal, o[1])) +
				 obb.size.z * fabsf(glm::dot(normal, o[2]));
	// Distance from the center of the OBB to the plane
	float dot = glm::dot(plane.normal, obb.position);
	float dist = dot - plane.distance;
	// Intersection occurs if the distance falls within the projected side
	return fabsf(dist) <= pLen;
}

// Plane vs OBB intersection
inline bool CheckIntersection(Plane& plane, OBB& obb) {
	return CheckIntersection(obb, plane);
}

// Plane vs Plane
bool CheckIntersection(Plane& p1, Plane& p2) {
	// Direction of the intersection line
	glm::vec3 dir = glm::cross(p1.normal, p2.normal);
	// Check the length of this new vector
	// if it is 0, the planes are parallel
	return !ET(MagnitudeSq(dir), 0.0f);
}