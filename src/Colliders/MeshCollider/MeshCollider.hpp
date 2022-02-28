#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include"BVHNode.hpp"

class MeshCollider {
public:
	// Number of triangles in mesh
	int numTriangles;
	union {
		Triangle* triangles;  // numTriangles
		glm::vec3* vertices;  // numTriangles * 3
		float* values;		  // numTriangles * 3 * 3
	};
	BVHNode* accelerator;
	// Constructors
	MeshCollider() : numTriangles(0), values(0), accelerator(0) {} // Empty
};


#endif