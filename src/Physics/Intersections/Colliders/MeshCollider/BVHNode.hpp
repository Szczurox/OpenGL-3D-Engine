#ifndef BHVNODE_CLASS_H
#define BHVNODE_CLASS_H

#include"../Triangle.hpp"
#include"../AABB.hpp"

class BVHNode {
public:
	// Number of triangles
	int numTriangles;
	int* triangles;
	// BVH's AABB
	AABB bounds;
	BVHNode* children;
	// Constructor
	BVHNode() : children(0), numTriangles(0), triangles(0) {};
};

#endif
