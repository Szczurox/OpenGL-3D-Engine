#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>
#include<vector>

#include"Utils/VAO.hpp"
#include"Utils/EBO.hpp"
#include"Camera.hpp"
#include"Texture.hpp"

class Mesh {
	public: 
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		VAO VAO;

		// Creates empty mesh
		Mesh() {};
		// Constructs a mesh using vertices, indices and textures
		Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
		// Constructs a mesh using vertices and indices (mainly for collider)
		Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

		// Draws a mesh
		void Draw (
			Shader& shader,
			Camera& camera,
			glm::mat4 matrix = glm::mat4(1.0f),
			glm::vec3 translation = glm::vec3(0.0f),
			glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
			glm::vec3 scale = glm::vec3(1.0f)
		);
	private:
		void calcVAO();
};

#endif
