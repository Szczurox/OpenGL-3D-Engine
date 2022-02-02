#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.h>
#include"Mesh.hpp"

using json = nlohmann::json;


class Model {
	public:
		// Model properties
		glm::vec3 position = glm::vec3(0.0f);
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		glm::vec3 scale = glm::vec3(1.0f);

		// Empty model
		Model();

		// Loads in a model from a file
		Model(const char* file);

		// Draws model
		void Draw(Shader& shader, Camera& camera);

	private:
		const char* file;
		std::vector<unsigned char> data;
		json JSON;

		// Meshes and transformations
		std::vector<Mesh> meshes;
		std::vector<glm::vec3> translationsMeshes;
		std::vector<glm::quat> rotationsMeshes;
		std::vector<glm::vec3> scalesMeshes;
		std::vector<glm::mat4> matricesMeshes;

		// Prevents textures from being loaded twice
		std::vector<std::string> loadedTexName;
		std::vector<Texture> loadedTex;

		// Loads a single mesh by its index
		void loadMesh(unsigned int indMesh);

		// Traverses all connected nodes
		void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

		// Gets the binary data from a file
		std::vector<unsigned char> getData();
		// Interprets the binary data into floats, indices, and textures
		std::vector<float> getFloats(json accessor);
		std::vector<GLuint> getIndices(json accessor);
		std::vector<Texture> getTextures();

		// Groups floats into vectors
		std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
		std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
		std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);

		// Assembles the grouped floats into vertices
		std::vector<Vertex> assembleVertices(
			std::vector<glm::vec3> positions,
			std::vector<glm::vec3> normal,
			std::vector<glm::vec2> texUV
		);
};

#endif // !MODEL_CLASS_H
