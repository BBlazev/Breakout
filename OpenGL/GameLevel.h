#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "ResourceManager.h"
#include "GameObject.h"
#include "SpriteRenderer.h"


class GameLevel
{
public:

	std::vector<GameObject> Bricks;
	GameLevel() {}
	void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);

	void Draw(SpriteRenderer& renderer, bool shake = false, float amount = 0.0f);

	bool IsCompleted();

private:

	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);

};

