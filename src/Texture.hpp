#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.hpp"

class Texture {
	public:
		// Reference ID of Texture
		GLuint ID;
		// Texture type
		const char* type;
		GLuint unit;
		// Constructor that generates Texture
		Texture(const char* image, const char* texType, GLuint slot);

		// Assigns a texture unit to a texture
		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		// Binds, Unbinds, Deletes Texture
		void Bind();
		void Unbind();
		void Delete();
};

#endif 
