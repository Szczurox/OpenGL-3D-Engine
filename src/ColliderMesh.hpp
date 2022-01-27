#ifndef COLLIDER_MESH_CLASS_H
#define COLLIDER_MESH_CLASS_H

#include<string>
#include<vector>

#include"VAO.hpp"
#include"EBO.hpp"
#include"Camera.hpp"
#include"Texture.hpp"

class ColliderMesh {
public:
	std::vector<Vertex> veritces;
	std::vector<GLuint> indices;

	VAO VAO;

	ColliderMesh();
	ColliderMesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

	void Generate(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
};

#endif
