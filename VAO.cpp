#include"VAO.h"

// Constructor that generates VAO (Vertex Array Object) ID
VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

// Links VBO to the VAO using a certain layout
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds VAO
void VAO::Bind() {
	glBindVertexArray(ID);
}

// Unbinds VAO
void VAO::Unbind() {
	glBindVertexArray(0);
}

// Deletes VAO
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}