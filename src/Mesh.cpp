#include"Mesh.hpp"

Mesh::Mesh() {}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) {
	Mesh::Generate(vertices, indices, textures);
}

void Mesh::Generate(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures) {
	Mesh::veritces = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	// Vertex Array Object
	VAO.Bind();

	// Vertex Buffer Object linked to veritces
	VBO VBO(vertices);
	// Element Buffer Object  linked to indices
	EBO EBO(indices);

	// Links VBO attributes to VAO 
	// Coordinates
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	// Colors
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	// Texture coordinates
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	// Normals
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	// Unbind all objects to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera) {
	shader.Activate();
	VAO.Bind();

	// Keep track of number of textures each type have
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;
		if (type == "diffuse") {
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular") {
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
	// Camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Draw the mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}