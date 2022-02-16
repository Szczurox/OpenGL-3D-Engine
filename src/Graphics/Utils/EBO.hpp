#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>


class EBO {
public:
	// Reference ID of EBO
	GLuint ID;
	// Constructor that creates EBO (Element Buffer Object) and links it to indices
	EBO(std::vector<GLuint>& indices);

	// Binds, Unbinds, Deletes EBO
	void Bind();
	void Unbind();
	void Delete();
};

#endif 
