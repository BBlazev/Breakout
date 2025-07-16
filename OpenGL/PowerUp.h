#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

#include "GameObject.h"

const glm::vec2 POWERUP_SIZE(60.0f, 20.0f);
// Velocity a PowerUp block has when spawned
const glm::vec2 VELOCITY(0.0f, 150.0f);


class PowerUp : public GameObject
{
public:

	std::string Type;
	float Duration;
	bool Activated;

	PowerUp(std::string type, glm::vec3 color, float duration, glm::vec2 pos, Texture2D texture) 
		: GameObject(pos, POWERUP_SIZE, texture, color, VELOCITY), Type(type), Duration(duration), Activated()
	{ }
	

};

