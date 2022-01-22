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

	// Create and compile the Fragment Shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Shader Program Object
	ID = glCreateProgram();

	// Attach Vertex Shader and Fragment Shader to Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Link all the shaders into the Shader Program
	glLinkProgram(ID);

	// Delete Vertex and Fragment Shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate() {
	glUseProgram(ID);
};

void Shader::Delete() {
	glDeleteProgram(ID);
}
