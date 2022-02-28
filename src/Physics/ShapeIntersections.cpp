#include"ShapeIntersections.hpp"

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

// Triangle vs Sphere
bool CheckIntersection(Triangle& tri, Sphere& sphere) {
	// Closest point on the triangle to the sphere
	glm::vec3 closest = ClosestPoint(tri, sphere.position);
	// Squared distance between the closest point and the  position of the sphere
	float sqDist = MagnitudeSq(closest - sphere.position);
	// Intersection occurs if the squared distance is less than the squared radius of the sphere
	return sqDist <= sphere.radius * sphere.radius;
}

// Sphere vs Triangle
inline bool CheckIntersection(Sphere& sphere, Triangle& tri) {
	return CheckIntersection(tri, sphere);
}

// Triangle vs AABB
bool CheckIntersection(Triangle& tri, AABB& aabb) {
	// Edge vectors of the triangle
	glm::vec3 e1 = tri.b - tri.a;
	glm::vec3 e2 = tri.c - tri.b;
	glm::vec3 e3 = tri.a - tri.c;
	// Face normals of the AABB
	glm::vec3 n1(1.0f, 0.0f, 0.0f);
	glm::vec3 n2(0.0f, 1.0f, 0.0f);
	glm::vec3 n3(0.0f, 0.0f, 1.0f);
	glm::vec3 axes[13] = {
		n1, // AABB Axis 1
		n2, // AABB Axis 2
		n3, // AABB Axis 3
		glm::cross(e1, e2), // Normal of the triangle
		// Cross products of every normal of the AABB with every edge of the triangle
		glm::cross(n1, e1), glm::cross(n1, e2), glm::cross(n1, e3),
		glm::cross(n2, e1), glm::cross(n2, e2), glm::cross(n2, e3),
		glm::cross(n3, e1), glm::cross(n3, e2), glm::cross(n3, e3),
	};
	// Check if AABB and Triangle are overlaping on all axes
	for (int i = 0; i < 13; ++i) {
		// If AABB and Triangle don't overlap on at least 1 axis, intersection doesn't occur
		if (!OverlapOnAxis(aabb, tri, axes[i])) {
			return false; // Separating axis found
		}
	}
	return true; // Separating axis not found
}

// AABB vs Triangle
inline bool CheckIntersection(AABB& aabb, Triangle& tri) {
	return CheckIntersection(tri, aabb);
}

// Triangle vs OBB
bool CheckIntersection(Triangle& tri, OBB& obb) {
	// Edge vectors of the triangle
	glm::vec3 e1 = tri.b - tri.a;
	glm::vec3 e2 = tri.c - tri.b;
	glm::vec3 e3 = tri.a - tri.c;
	// Face normals of the OBB
	glm::mat3 o = obb.orientation;
	glm::vec3 n1(o[0].x, o[0].y, o[0].z);
	glm::vec3 n2(o[1].x, o[1].y, o[1].z);
	glm::vec3 n3(o[2].x, o[2].y, o[2].z);
	glm::vec3 axes[13] = {
		n1, // AABB Axis 1
		n2, // AABB Axis 2
		n3, // AABB Axis 3
		glm::cross(e1, e2), // Normal of the triangle
		// Cross products of every normal of the AABB with every edge of the triangle
		glm::cross(n1, e1), glm::cross(n1, e2), glm::cross(n1, e3),
		glm::cross(n2, e1), glm::cross(n2, e2), glm::cross(n2, e3),
		glm::cross(n3, e1), glm::cross(n3, e2), glm::cross(n3, e3),
	};
	// Check if OBB and Triangle are overlaping on all axes
	for (int i = 0; i < 13; ++i) {
		// If OBB and Triangle don't overlap on at least 1 axis, intersection doesn't occur
		if (!OverlapOnAxis(obb, tri, axes[i])) {
			return false; // Separating axis found
		}
	}
	return true; // Separating axis not found
}

// OBB vs Triangle
inline bool CheckIntersection(OBB& obb, Triangle& tri) {
	return CheckIntersection(tri, obb);
}

// Triangle vs Plane
bool CheckIntersection(Triangle& tri, Plane& plane) {
	// On which side of the plane is every point of the triangle
	float s1 = PlaneEquation(tri.a, plane);
	float s2 = PlaneEquation(tri.b, plane);
	float s3 = PlaneEquation(tri.c, plane);
	
	// If all points are on the plane, the plain and the triangle are intersecting
	if (ET(s1, 0) && ET(s2, 0) && ET(s3, 0)) 
		return true;

	// If all points of the triangle are behind or in front of the plane,
	// intersection doesn't occur
	if ((s1 < 0 && s2 < 0 && s3 < 0) || (s1 > 0 && s2 > 0 && s3 > 0))
		return false;
	
	// 1 point is on the opposite side of the plane than the other 2, intersection occurs
	return true;
}

// Plane vs Triangle
inline bool CheckIntersection(Plane& plane, Triangle& tri) {
	return CheckIntersection(tri, plane);
}

bool CheckIntersection(Triangle& tri1, Triangle& tri2) {
	glm::vec3 axes[11] = {
		SatCrossEdge(tri1.a, tri1.b, tri1.b, tri1.c), // Normal of the first triangle
		SatCrossEdge(tri2.a, tri2.b, tri2.b, tri2.c), // Normal of the first triangle

		// Better cross products for every edge of the triangles
		SatCrossEdge(tri2.a, tri2.b, tri1.a, tri1.b),
		SatCrossEdge(tri2.a, tri2.b, tri1.b, tri1.c),
		SatCrossEdge(tri2.a, tri2.b, tri1.c, tri1.a),

		SatCrossEdge(tri2.b, tri2.c, tri1.a, tri1.b),
		SatCrossEdge(tri2.b, tri2.c, tri1.b, tri1.c),
		SatCrossEdge(tri2.b, tri2.c, tri1.c, tri1.a),

		SatCrossEdge(tri2.c, tri2.a, tri1.a, tri1.b),
		SatCrossEdge(tri2.c, tri2.a, tri1.b, tri1.c),
		SatCrossEdge(tri2.c, tri2.a, tri1.c, tri1.a),
	};
	// Check if Triangles are overlaping on all axes
	for (int i = 0; i < 11; ++i) {
		if (!OverlapOnAxis(tri1, tri2, axes[i])) {
			// If the edges being tested are on a straight line, the SatCrossEdge function returns a zero vector
			// This will prevent any axis with a length of zero from returning true
			if (!ET(MagnitudeSq(axes[i]), 0)) {
				return false; // Seperating axis found
			}
		}
	}
	return true; // Seperating axis not found
}