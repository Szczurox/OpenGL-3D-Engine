#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cerrno>

#include"shaderClass.hpp"

class Texture {
	public:
		// Reference ID of Texture
		GLuint ID;
		// Texture type
		GLenum type;
		GLuint unit;
		// Width and height of loaded image in pixels
		//unsigned int width, height;
		//// Format of texture object
		//unsigned int internalFormat;
		//// Format of loaded image
		//unsigned int imageFormat;
		//// Texture configuration
		//unsigned int wrapS; // Wrapping mode on S axis
		//unsigned int wrapT; // Wrapping mode on T axis
		//unsigned int filterMin; // Filtering mode if texture pixels < screen pixels
		//unsigned int filterMax; // Filtering mode if texture pixels > screen pixels
		//unsigned int texType; // Texture type
		//unsigned int pixelType; // Data type of pixel data
		// Constructor that generates Texture
		Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType);
		//void Generate(unsigned char* bytes, GLuint slot);
		// Assigns a texture unit to a texture
		void texUnit(Shader& shader, const char* uniform, GLuint unit);
		// Binds, Unbinds, Deletes Texture
		void Bind();
		void Unbind();
		void Delete();
};

#endif 
