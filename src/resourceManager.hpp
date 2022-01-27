#ifndef RESOURCE_MANAGER_CLASS_H
#define RESOURCE_MANAGER_CLASS_H

#include<map>

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cerrno>
#include<glad/glad.h>
#include<stb/stb_image.h>

#include"Texture.hpp"
#include"shaderClass.hpp"

// Functions to load Textures and Shaders
// Each loaded texture and shader is stored for future reference by string handles
class ResourceManager {
    public:
        static std::string get_file_contents(const char* filename);
        // Resource storage
        static std::map<std::string, Shader>    Shaders;
        static std::map<std::string, Texture> Textures;
        // Loads and generates a shader program from file loading vertex and fragment shader's source code
        static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
        // Gets a stored shader
        static Shader GetShader(std::string name);
        // Loads and generates a texture from file
        static Texture LoadTexture(const char* file, std::string name, GLuint slot = 0);
        static Texture LoadTexture(const char* file, std::string name, Shader shader, GLuint slot = 0);
        static Texture LoadTexture(const char* file, std::string name, Shader shader, const char* uniform, GLuint slot = 0);
        // Gets a stored texture
        static Texture GetTexture(std::string name);
        // Properly deletes all loaded resources
        static void Clear();
    private:
        ResourceManager() { }
        // Loads and generates a shader from file
        static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile);
        // Loads a single texture from file
        static Texture loadTextureFromFile(const char* file, unsigned int slot);
};

#endif