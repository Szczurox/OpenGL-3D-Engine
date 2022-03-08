#ifndef SHAPE_INTERSECTION_H
#define SHAPE_INTERSECTION_H

#include<vector>
#include<variant>
#include"PointTests.hpp"

template<class T, class U>
bool CheckIntersection(T t, U u);

// Sphere vs Sphere
template<>
bool CheckIntersection<Sphere&, Sphere&>(Sphere& s1, Sphere& s2);
// Sphere vs AABB
template<>
bool CheckIntersection<Sphere&, AABB&>(Sphere& sphere, AABB& aabb);
template<>
bool CheckIntersection<AABB&, Sphere&>(AABB& aabb, Sphere& sphere);
// Sphere vs OBB
template<>
bool CheckIntersection<Sphere&, OBB&>(Sphere& sphere, OBB& obb);
template<>
bool CheckIntersection<OBB&, Sphere&>(OBB& obb, Sphere& sphere);
// Sphere vs Plane
template<>
bool CheckIntersection<Sphere&, Plane&>(Sphere& sphere, Plane& plane);
template<>
bool CheckIntersection<Plane&, Sphere&>(Plane& plane, Sphere& sphere);
// AABB vs AABB
template<>
bool CheckIntersection<AABB&, AABB&>(AABB& a, AABB& b);
// AABB vs OBB
template<>
bool CheckIntersection<AABB&, OBB&>(AABB& aabb, OBB& obb);
template<>
bool CheckIntersection<OBB&, AABB&>(OBB& obb, AABB& aabb); 
// AABB vs Plane
template<>
bool CheckIntersection<AABB&, Plane&>(AABB& aabb, Plane& plane);
template<>
bool CheckIntersection<Plane&, AABB&>(Plane& plane, AABB& aabb);
// OBB vs OBB
template<>
bool CheckIntersection<OBB&, OBB&>(OBB& obb1, OBB& obb2);
// OBB vs Plane
template<>
bool CheckIntersection<OBB&, Plane&>(OBB& obb, Plane& plane);
template<>
bool CheckIntersection<Plane&, OBB&>(Plane& plane, OBB& obb);
// Plane vs Plane
template<>
bool CheckIntersection<Plane&, Plane&>(Plane& p1, Plane& p2);
// Triangle vs Sphere
template<>
bool CheckIntersection<Triangle&, Sphere&>(Triangle& tri , Sphere& sphere);
template<>
bool CheckIntersection<Sphere&, Triangle&>(Sphere& sphere, Triangle& tri);
// Triangle vs AABB
template<>
bool CheckIntersection<Triangle&, AABB&>(Triangle& tri, AABB& aabb);
template<>
bool CheckIntersection<AABB&, Triangle&>(AABB& aabb, Triangle& tri);
// Triangle vs OBB
template<>
bool CheckIntersection<Triangle&, OBB&>(Triangle& tri, OBB& obb);
template<>
bool CheckIntersection<OBB&, Triangle&>(OBB& obb, Triangle& tri);
// Triangle vs Plane
template<>
bool CheckIntersection<Triangle&, Plane&>(Triangle& tri, Plane& plane);
template<>
bool CheckIntersection<Plane&, Triangle&>(Plane& plane, Triangle& tri);
// Triangle vs Triangle
template<>
bool CheckIntersection<Triangle&, Triangle&>(Triangle& tri1, Triangle& tri2);


// I had to put the source code to this functions in here because I use template
// Mesh vs AABB
template<class T>
bool CheckIntersection(MeshCollider& mesh, T collider) {
	// If the mesh has no accelerator structure, we loop through the triangles
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.numTriangles; ++i)
			// Check for intersection
			if (CheckIntersection<Triangle&, T>(mesh.triangles[i], collider))
				return true;
	}
	else {
		std::list<BVHNode*> toProcess;
		toProcess.push_front(mesh.accelerator);
		// Walk through the BVH tree looking for intersection
		while (!toProcess.empty()) {
			BVHNode* iterator = *(toProcess.begin());
			toProcess.erase(toProcess.begin());
			// If the BVH node has triangles, check every triangle of the node for intersection
			if (iterator->numTriangles >= 0) {
				for (int i = 0; i < iterator->numTriangles; ++i) {
					// If is intersecting, return true
					if (CheckIntersection<Triangle&, T>(mesh.triangles[iterator->triangles[i]], collider))
						return true;
				}
			}
			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// If is intersecting, add the node to the list of nodes to process
					if (CheckIntersection<AABB&, T>(iterator->children[i].bounds, collider))
						toProcess.push_front(&iterator->children[i]);
				}
			}
		}
	}
	// If no intersection was detected, return false
	return false;
}

#endif