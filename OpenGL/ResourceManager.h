#pragma once

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "stb_image.h"
#include <glad/glad.h>

#include "Texture2D.h"
#include "Shader.h"



class ResourceManager
{
public:
	static std::map<std::string,Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;

	static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	static Shader GetShader(std::string name);

	static Texture2D LoadTexture(const char* file, bool aplha, std::string name);
	static Texture2D GetTexture(std::string name);

	static void clear();

private:
	ResourceManager() {}
	static Shader loadShaderFromFIle(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static Texture2D loadTextureFromFIle(const char* file, bool alpha);
};

