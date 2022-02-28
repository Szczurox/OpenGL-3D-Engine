#ifndef MESH_COLLIDER_HELPERS_H
#define MESH_COLLIDER_HELPERS_H

#include"MeshCollider.hpp"
#include"../../Physics/ShapeIntersections.hpp"

// Creates the root BVHNode for the provided mesh
void AccelerateMesh(MeshCollider& mesh);
// Recursively splits the BVHNode until a given depth is reached
void SplitBVHNode(BVHNode* node, MeshCollider& model, int depth);
// Recursively deletes all children of the provided node
void FreeBVHNode(BVHNode* node);

#endif