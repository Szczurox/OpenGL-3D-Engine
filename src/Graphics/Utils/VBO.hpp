#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO {
	public:
		// Reference ID of the VBO (Vertex Buffer Object)
		GLuint ID;
		// Constructor that generates VBO and links it to vertices
		VBO(std::vector<Vertex>& vertices);

		// Binds Vertex Buffer Object
		void Bind();
		// Unbinds Vertex Buffer Object
		void Unbind();
		// Deletes Vertex Buffer Object
		void Delete();
};

#endif 
