#include"VBO.h"

// Constructor that generates VBO and links it to vertices
VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

// Binds Vertex Buffer Object
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds Vertex Buffer Object
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes Vertex Buffer Object
void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}