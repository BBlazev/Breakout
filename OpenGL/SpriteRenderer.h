#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "Shader.h"


class SpriteRenderer
{
public:
	SpriteRenderer(const Shader& shader);
	~SpriteRenderer();
	void DrawSprite(const Texture2D& texture, glm::vec2 positioon, glm::vec2 size = glm::vec2(10.f, 10.f),
					float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
	Shader shader;
	unsigned int quadVAO;
	void initRenderData();

};

