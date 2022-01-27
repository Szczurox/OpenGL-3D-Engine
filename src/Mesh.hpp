#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>
#include<vector>

#include"VAO.hpp"
#include"EBO.hpp"
#include"Camera.hpp"
#include"Texture.hpp"

class Mesh {
public:
	std::vector<Vertex> veritces;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	VAO VAO;

<<<<<<< HEAD
	Mesh();
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

	void Draw(Shader& Shader, Camera& Camera);
=======
		Mesh();
		Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

		void Generate(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
		void Draw(Shader& Shader, Camera& Camera);
>>>>>>> parent of 73c726d (Revert "Objects")
};

#endif