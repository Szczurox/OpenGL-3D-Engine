#include"ColliderMesh.hpp"

ColliderMesh::ColliderMesh() {}

ColliderMesh::ColliderMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {
	ColliderMesh::Generate(vertices, indices);
}

void ColliderMesh::Generate(std::vector <Vertex>& vertices, std::vector <GLuint>& indices) {
	ColliderMesh::veritces = vertices;
	ColliderMesh::indices = indices;

	// Vertex Array Object
	VAO.Bind();

	// Vertex Buffer Object linked to veritces
	VBO VBO(vertices);
	// Element Buffer Object  linked to indices
	EBO EBO(indices);

	// Coordinates
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);

	// Unbind all objects to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}
