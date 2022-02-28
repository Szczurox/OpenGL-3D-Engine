#include"MeshHelpers.hpp"

// Creates the root BVHNode for the provided mesh
void AccelerateMesh(MeshCollider &mesh) {
	// Return if mesh already have accelerator
	if (mesh.accelerator != 0)
		return;

	// Minimum and maximum points of the mesh
	glm::vec3 min = mesh.vertices[0];
	glm::vec3 max = mesh.vertices[0];
	for (int i = 1; i < mesh.numTriangles * 3; ++i) {
		min.x = fminf(mesh.vertices[i].x, min.x);
		min.y = fminf(mesh.vertices[i].y, min.y);
		min.z = fminf(mesh.vertices[i].z, min.z);
		max.x = fmaxf(mesh.vertices[i].x, max.x);
		max.y = fmaxf(mesh.vertices[i].y, max.y);
		max.z = fmaxf(mesh.vertices[i].z, max.z);
	}
	// Add new accelerator structure to the mesh
	mesh.accelerator = new BVHNode();
	// Set the AABB bounds to the min and max points of the mesh
	mesh.accelerator->bounds = AABBFromMinMax(min, max);
	mesh.accelerator->numTriangles = mesh.numTriangles;
	// Allocate memory for the triangle indices
	mesh.accelerator->triangles = new int[mesh.numTriangles];
	for (int i = 0; i < mesh.numTriangles; ++i) 
		mesh.accelerator->triangles[i] = i;
	// Split the BVHNode
	SplitBVHNode(mesh.accelerator, mesh, 3);
}

// Recursively splits the BVHNode until a given depth is reached
void SplitBVHNode(BVHNode* node, MeshCollider& mesh, int depth) {
	// Decrements depth and returns when depth is 0
	if (depth-- == 0)
		return;
	// If the node is a leaf (it has no children) split it into eight child nodes
	if (node->children == 0) {
		// Split if this node contains triangles
		if (node->numTriangles > 0) {
			// Allocate memory for the children of this node
			node->children = new BVHNode[8];
			// Set the extents of each child node
			glm::vec3 c = node->bounds.position;
			glm::vec3 e = node->bounds.size * 0.5f;
			node->children[0].bounds = AABB(c + glm::vec3(-e.x, e.y, -e.z), e);
			node->children[1].bounds = AABB(c + glm::vec3(e.x, e.y, -e.z), e);
			node->children[2].bounds = AABB(c + glm::vec3(-e.x, e.y, e.z), e);
			node->children[3].bounds = AABB(c + glm::vec3(e.x, e.y, e.z), e);
			node->children[4].bounds = AABB(c + glm::vec3(-e.x, -e.y, -e.z), e);
			node->children[5].bounds = AABB(c + glm::vec3(e.x, -e.y, -e.z), e);
			node->children[6].bounds = AABB(c + glm::vec3(-e.x, -e.y, e.z), e);
			node->children[7].bounds = AABB(c + glm::vec3(e.x, -e.y, e.z), e);
		}
	}
	// If the node has children and triangles, 
	// assign each child node its own list of triangles that the child node intersects
	if (node->children != 0 && node->numTriangles > 0) {
		for (int i = 0; i < 8; ++i) {
			node->children[i].numTriangles = 0;
			// Loop through every triangle and check if it intersects the bounds of the child node
			for (int j = 0; j < node->numTriangles; ++j) {
				Triangle t = mesh.triangles[node->triangles[j]];
				// If the triangle intersects bounds of this node, increase triangle count
				if (CheckIntersection(t, node->children[i].bounds))
					node->children[i].numTriangles += 1;
			}
			if (node->children[i].numTriangles == 0)
				continue;
			// Allocate new memory for the indices of the child node
			node->children[i].triangles = new int[node->children[i].numTriangles];
			int index = 0;
			// For every triangle that intersects the child node,
			// add its index to the list of triangle indices
			for (int j = 0; j < node->numTriangles; ++j) {
				Triangle t = mesh.triangles[node->triangles[j]];
				if (CheckIntersection(t, node->children[i].bounds))
					node->children[i].triangles[index++] = node->triangles[j];
			}
			node->numTriangles = 0;
			delete[] node->triangles;
			node->triangles = 0;

			for (int i = 0; i < 8; ++i)
				SplitBVHNode(&node->children[i], mesh, depth);
		}
	}
}

void FreeBVHNode(BVHNode* node) {
	// If there are any children
	if (node->children != 0) {
		// Recursively clear the data of all child nodes
		for (int i = 0; i < 8; ++i)
			FreeBVHNode(&node->children[i]);
		delete[] node->children;
		node->children = 0;
	}
	// If triangle indices are present, release the array holding them
	if (node->numTriangles != 0 || node->triangles != 0) {
		node->triangles = 0;
		delete[] node->triangles;
		node->numTriangles = 0;
	}
}