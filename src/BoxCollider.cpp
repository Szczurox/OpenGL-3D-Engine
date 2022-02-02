#include "BoxCollider.hpp"

// Cuboid
BoxCollider::BoxCollider(GLfloat width, GLfloat height, GLfloat depth)
	: width(width), height(height), depth(depth) {

}

// Cube
BoxCollider::BoxCollider(GLfloat width) 
	: height(width), depth(width) {
	GLfloat halfWidth = width / 2;
	// Calculate vertices coordinates
	Vertex vertices[] = {
		Vertex{glm::vec3(-halfWidth, -halfWidth, halfWidth)},
		Vertex{glm::vec3(-halfWidth, -halfWidth, -halfWidth)},
		Vertex{glm::vec3(halfWidth, -halfWidth, -halfWidth)},
		Vertex{glm::vec3(halfWidth, -halfWidth,  halfWidth)},
		Vertex{glm::vec3(-halfWidth,  halfWidth,  halfWidth)},
		Vertex{glm::vec3(-halfWidth,  halfWidth, -halfWidth)},
		Vertex{glm::vec3(halfWidth,  halfWidth, -halfWidth)},
		Vertex{glm::vec3(halfWidth,  halfWidth,  halfWidth)} 
	};
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> inds(colliderIndices, colliderIndices + sizeof(colliderIndices) / sizeof(GLuint));
	// Create collider mesh
	Mesh collider(verts, inds);
}