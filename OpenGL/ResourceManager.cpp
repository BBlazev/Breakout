#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;


Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFIle(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFIle(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::clear()
{
    for (auto it : Shaders)
        glDeleteProgram(it.second.ID);
    for (auto it : Textures)
        glDeleteTextures(1, &it.second.ID);
}

Shader ResourceManager::loadShaderFromFIle(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try {
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);

        std::stringstream vertexSStream, fragmentSStream;

        vertexSStream << vertexShaderFile.rdbuf();
        fragmentSStream << fragmentShaderFile.rdbuf();

        vertexCode = vertexSStream.str();
        fragmentCode = fragmentSStream.str();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();

    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

    return shader;
}

Texture2D ResourceManager::loadTextureFromFIle(const char* file, bool alpha)
{
    Texture2D texture;
    if (alpha) {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    int w, h, nrChannel;
    unsigned char* data = stbi_load(file, &w, &h, &nrChannel, 0);

    texture.Generate(w, h, data);

    return texture;
}
