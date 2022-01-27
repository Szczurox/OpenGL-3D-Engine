#include"Texture.hpp"

//Texture::Texture()
//	: type(GL_TEXTURE_2D), unit(0), width(0), height(0), internalFormat(GL_RGBA), imageFormat(GL_RGBA), 
//	wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_NEAREST), filterMax(GL_NEAREST), texType(GL_TEXTURE_2D),
//	pixelType(GL_UNSIGNED_BYTE)
//{
//	glGenTextures(1, &ID);
//}
//
//// Constructor that generates Texture
//void Texture::Generate(unsigned char* bytes, GLuint slot) {
//	unit = slot;
//
//	std::cout << type;
//	glActiveTexture(GL_TEXTURE0 + slot);
//	// Assigns the texture to a Texture Unit
//	glBindTexture(texType, ID);
//
//	// Configures algorithm used to make the image smaller or bigger
//	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, filterMin);
//	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, filterMax);
//
//	// Configures the way the texture repeats
//	glTexParameteri(texType, GL_TEXTURE_WRAP_S, wrapS);
//	glTexParameteri(texType, GL_TEXTURE_WRAP_T, wrapT);
//
//	// Assigns the image to the Texture object
//	glTexImage2D(texType, 0, internalFormat, width, height, 0, imageFormat, pixelType, bytes);
//	// Generates MipMaps
//	glGenerateMipmap(texType);
//
//	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
//	glBindTexture(texType, 0);
//}
//
//// Assigns a texture unit to a texture
//void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
//	// Gets the location of the uniform
//	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
//	// Activates shader (required before uniform can be accessed))
//	shader.Activate();
//	std::cout << texUni;
//	// Sets the value of the uniform
//	glUniform1i(texUni, unit);
//}
//
//// Binds Texture
//void Texture::Bind() {
//	glActiveTexture(GL_TEXTURE0 + unit);
//	glBindTexture(type, ID);
//}
//
//// Unbinds Texture
//void Texture::Unbind() {
//	glBindTexture(type, 0);
//}
//
//// Deletes Texture
//void Texture::Delete() {
//	glDeleteTextures(1, &ID);
//}

Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType) {
	// Assigns the type of the texture ot the texture object
	type = texType;

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(texType, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Assigns the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(texType);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}