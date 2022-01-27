#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO {
	public:
		// Reference ID of the VBO (Vertex Buffer Object)
		GLuint ID;
		// Constructor that generates VBO and links it to vertices
		VBO(GLfloat* vertices, GLsizeiptr size);

		// Binds Vertex Buffer Object
		void Bind();
		// Unbinds Vertex Buffer Object
		void Unbind();
		// Deletes Vertex Buffer Object
		void Delete();
};

#endif 
