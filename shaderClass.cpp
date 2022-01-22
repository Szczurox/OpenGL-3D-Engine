#include"shaderClass.h"

// Reads text file and outputs string with text file content
std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Constructor that builds the Shader Program from 2 shaders
Shader::Shader(const char* vertFile, const char* fragFile) {
	// Get shaders source from files
	std::string vertCode = get_file_contents(vertFile);
	std::string fragCode = get_file_contents(fragFile);

	// Convert shader source strings into character arrays
	const char* vertexSource = vertCode.c_str();
	const char* fragmentSource = fragCode.c_str();

	// Create and compile the Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	// Checks if the Shader compiled successfully
	compileErrors(vertexShader, "VERTEX");

	// Create and compile the Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	// Checks if the Shader compiled successfully
	compileErrors(fragmentShader, "FRAGMENT");

	// Shader Program Object
	ID = glCreateProgram();
	// Checks if the Shaders linked successfully
	compileErrors(ID, "PROGRAM");

	// Attach Vertex Shader and Fragment Shader to Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Link all the shaders into the Shader Program
	glLinkProgram(ID);

	// Delete Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// Activates the Shader Program
void Shader::Activate() {
	glUseProgram(ID);
};

// Deletes the Shader Program
void Shader::Delete() {
	glDeleteProgram(ID);
}

// Checks is the shaders compiled/linked properly
void Shader::compileErrors(unsigned int shader, const char* type) {
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	}
	else {
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}