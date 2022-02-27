#include"LineIntersections.hpp"

// Raycast Sphere
float Raycast(Sphere& sphere, Ray& ray) {
	// t - distance between the ray origin and the sphere surface
	// t = a - f
	// f = sqrt(r^2 - b^2)
	// b^2 = e^2 - a^2
	// t = a - sqrt(r ^ 2 - (e ^ 2 - a ^ 2))

	// Vector from the origin of the ray to the center of the sphere
	glm::vec3 e = sphere.position - ray.origin;
	// Squared radius and squared magnitude of the e vector
	float rSq = sphere.radius * sphere.radius;
	float eSq = MagnitudeSq(e);
	// Vector e projected onto the direction of the ray
	float a = glm::dot(e, ray.direction);
	// Construct the sides a triangle using the radius of the circle at the projected point
	// Sides of the triangle are r, b and f (all squared)
	float bSq = eSq - (a * a);
	float f = sqrt(rSq - bSq);

	// No collision has happened
	if (rSq - (eSq - (a * a)) < 0.0f) 
		return -1;
	// Ray starts inside the sphere
	else if (eSq < rSq) 
		return a + f; // Reverse direction
	// Normal intersection
	return a - f;
}

// Raycast AABB
float Raycast(AABB& aabb, Ray& ray) {
	// Get AABB's min and max points
	glm::vec3 min = aabb.GetMin();
	glm::vec3 max = aabb.GetMax();
	// Intersections of the ray against each of the three slabs which make up the AABB
	float tMinX = (min.x - ray.origin.x) / ray.direction.x;
	float tMaxX = (max.x - ray.origin.x) / ray.direction.x;
	float tMinY = (min.y - ray.origin.y) / ray.direction.y;
	float tMaxY = (max.y - ray.origin.y) / ray.direction.y;
	float tMinZ = (min.z - ray.origin.z) / ray.direction.z;
	float tMaxZ = (max.z - ray.origin.z) / ray.direction.z;
	// Largest minimum value
	float tMin = fmaxf(fmaxf(fminf(tMinX, tMaxX),fminf(tMinY, tMaxY)),fminf(tMinZ, tMaxZ));
	// Smallest maximum value
	float tMax = fminf(fminf(fmaxf(tMinX, tMaxX),fmaxf(tMinY, tMaxY)),fmaxf(tMinZ, tMaxZ));
	// AABB is on a line with the ray, but the ray points in a different direction
	if (tMax < 0) {
		return -1;
	}
	// Doesn't intersect
	if (tMin > tMax) {
		return -1;
	}
	// Ray intersects the AABB but its origin is inside the AABB
	if (tMin < 0.0f) {
		return tMax;
	}
	// Intersects
	return tMin;
}

// Raycast OBB
float Raycast(OBB& obb, Ray& ray) {
	// Get OBB's orientation and size
	glm::mat3 o = obb.orientation;
	glm::vec3 s = obb.size;
	// X, Y and Z axis of the OBB
	glm::vec3 x(o[0].x, o[0].y, o[0].z);
	glm::vec3 y(o[1].x, o[1].y, o[1].z);
	glm::vec3 z(o[2].x, o[2].y, o[2].z);
	// Vector pointing from origin of the ray to the OBB
	glm::vec3 p = obb.position - ray.origin;
	// All axes of the OBB with ray direction projected onto each of them
	glm::vec3 f(glm::dot(x, ray.direction), glm::dot(y, ray.direction), glm::dot(z, ray.direction));
	// Project p onto all exes of the OBB
	glm::vec3 e(glm::dot(x, p), glm::dot(y, p), glm::dot(z, p));
	float t[6] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 3; ++i) {
		if (ET(f[i], 0)) {
			// No hit if the ray is parallel to the tested slab
			// and the origin of the ray is not inside the tested slab
			if (-e[i] - s[i] > 0 || -e[i] + s[i] < 0) {
				return -1;
			}
			f[i] = 0.00001f;
		}
		t[i * 2 + 0] = (e[i] + s[i]) / f[i]; // Min
		t[i * 2 + 1] = (e[i] - s[i]) / f[i]; // Max
	}
	// Largest minimum value
	float tMin = fmaxf(fmaxf(fminf(t[0], t[1]),fminf(t[2], t[3])),fminf(t[4], t[5]));
	// Smallest maxiumum value
	float tMax = fminf(fminf(fmaxf(t[0], t[1]),fmaxf(t[2], t[3])),fmaxf(t[4], t[5]));
	// OBB is on a line with the ray, but the ray points in a different direction
	if (tMax < 0) {
		return -1;
	}
	// Doesn't intersect
	if (tMin > tMax) {
		return -1;
	}
	// Ray intersects the OBB but its origin is inside the OBB
	if (tMin < 0.0f) {
		return tMax;
	}
	// Intersects
	return tMin;
}

// Raycast Plane
float Raycast(Plane& plane, Ray& ray) {
	// t = (plane distance - (ray origin * plane normal)) / (ray direction * plane normal)
	float dirN = glm::dot(ray.direction, plane.normal);
	float oriN = glm::dot(ray.origin, plane.normal);
	// If dirN is positive or 0, the ray and plane normals point in the same direction
	// and there is no intersection
	if (dirN >= 0.0f) {
		return -1;
	}
	float t = (plane.distance - oriN) / dirN;
	// If t is negative, the ray hits the plane behind its origin so it did not hit it
	if (t < 0.0f) {
		return -1;
	}
	// Intersecting
	return t;
}

// Raycast Triangle
float Raycast(Triangle& tri, Ray& ray) {
	// Create a plane from the triangle
	Plane plane = PlaneFromTriangle(tri);
	float t = Raycast(plane, ray); 
	if (t < 0.0f)
		return t;
	// Point on the plane where the ray hit
	glm::vec3 result = ray.origin + ray.direction * t;
	// Barycentric coordinates of the Raycast on the plane
	glm::vec3 bar = Barycentric(result, tri);
	// If the point is within the triangle, the ray hit the triangle
	if (bar.x >= 0.0f && bar.x <= 1.0f && bar.y >= 0.0f && bar.y <= 1.0f && bar.z >= 0.0f && bar.z <= 1.0f)
		return t;

	// Ray did not hit the triangle
	return -1;
}

// Linetest Sphere
bool Linetest(Sphere& sphere, Line& line) {
	// Closest point to the center of the sphere along the line segment
	glm::vec3 closest = ClosestPoint(line, sphere.position);
	// Squared distance between the closest point and the center of the sphere
	float distSq = MagnitudeSq(sphere.position - closest);
	// If the distance is less than the magnitude, intersection occurs
	return distSq <= (sphere.radius * sphere.radius);
}

// Linetest AABB
bool Linetest(AABB& aabb, Line& line) {
	// Raycast AABB
	Ray ray = RayFromLine(line);
	float t = Raycast(aabb, ray);
	// If t is less than the length of the line, the segment intersects the AABB
	return t >= 0 && t * t <= LengthSq(line);
}

// Linetest OBB
bool Linetest(OBB& obb, Line& line) {
	// Raycast AABB
	Ray ray = RayFromLine(line);
	float t = Raycast(obb, ray);
	// If t is less than the length of the line, the segment intersects the OBB
	return t >= 0 && t * t <= LengthSq(line);
}

// Linetest Plane
bool Linetest(const Plane& plane, const Line& line) {
	// t = (plane distance * A) / (plane normal * (B - A))
	glm::vec3 ab = line.end - line.start;
	float nA = glm::dot(plane.normal, line.start);
	float nAB = glm::dot(plane.normal, ab);
	// If the line and plane are parallel, nAB will be 0
	// In this case we have to set it to some small number, but not 0 to prevent an exception
	if (!nAB) nAB = 0.0000001f;
	float t = (plane.distance - nA) / nAB;
	// Plane and Line intersect if the value of t falls within the 0 to 1 range
	return t >= 0.0f && t <= 1.0f;
}

// Linetest Triangle
bool Linetest(Triangle& triangle, Line& line) {
	// Construct a ray out of the line being tested
	Ray ray = RayFromLine(line);
	// Raycasts triangle
	float t = Raycast(triangle, ray);
	// If t is less than the length of the line, the segment intersects the Triangle
	return t >= 0 && t * t <= LengthSq(line);
}