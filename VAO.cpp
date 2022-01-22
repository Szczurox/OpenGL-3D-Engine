#include"VAO.h"

// Constructor that generates VAO (Vertex Array Object) ID
VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

// Links VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO VBO, GLuint layout) {
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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