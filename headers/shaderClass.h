#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader {
	public:
		// Reference ID of the Shader Program
		GLuint ID;
		// Constructor that builds the Shader Program from 2 shaders
		Shader(const char* vertexFile, const char* fragment);

		// Activates the Shader Program
		void Activate();
		// Deletes the Shader Program
		void Delete();
	private:
		// Checks is the shaders compiled/linked properly
		void compileErrors(unsigned int shader, const char* type);
};

#endif