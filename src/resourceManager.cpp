#include "resourceManager.hpp"


// Reads text file and outputs string with text file content
std::string ResourceManager::get_file_contents(const char* filename) {
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


// Instantiate static variables
std::map<std::string, Texture> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;


// Shaders //
Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile) {
    std::string vShaderCode = get_file_contents(vShaderFile);
    std::string fShaderCode = get_file_contents(fShaderFile);
    // Get shaders source from files

    // Convert shader source strings into character arrays
    const char* vertexSource = vShaderCode.c_str();
    const char* fragmentSource = fShaderCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vertexSource, fragmentSource);
    return shader;
}

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name) {
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name) {
    return Shaders[name];
}



//// Textures //
//Texture ResourceManager::loadTextureFromFile(const char* image, unsigned int slot) {
//    // Create texture object
//    Texture texture;
//    int widthImg, heightImg, numColCh;
//    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
//    texture.Generate(bytes, slot);
//    stbi_image_free(bytes);
//    return texture;
//}
//
//Texture ResourceManager::LoadTexture(const char* file, std::string name, GLuint slot) {
//    Textures[name] = loadTextureFromFile(file, slot);
//    return Textures[name];
//}
//
//Texture ResourceManager::LoadTexture(const char* file, std::string name, Shader shader, GLuint slot) {
//    Textures[name] = loadTextureFromFile(file, slot);
//    Textures[name].texUnit(shader, ("tex"+std::to_string(slot)).c_str(), slot);
//    return Textures[name];
//}
//
//Texture ResourceManager::LoadTexture(const char* file, std::string name, Shader shader, const char* uniform, GLuint slot) {
//    Textures[name] = loadTextureFromFile(file, slot);
//    Textures[name].texUnit(shader, uniform, slot);
//    return Textures[name];
//}
//
//Texture ResourceManager::GetTexture(std::string name) {
//    return Textures[name];
//}


void ResourceManager::Clear() {
    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}