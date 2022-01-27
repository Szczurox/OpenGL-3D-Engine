#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cerrno>


class Shader {
	public:
		// Reference ID of the Shader Program
		GLuint ID;
		// Constructor that builds the Shader Program from 2 shaders
		Shader() { };
		// Activates the Shader Program
		Shader& Activate();
		// Compile shader program from 2 vertex source code and fragment source code
		void Compile(const char* vertexSource, const char* fragmentSource);
		// Deletes the Shader Program
		void Delete();
	private:
		// Checks is the shaders compiled/linked properly
		void compileErrors(unsigned int shader, const char* type);
};

#endif