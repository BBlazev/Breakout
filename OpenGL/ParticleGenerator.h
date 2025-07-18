#pragma once
#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>


#include "Shader.h"
#include "Texture2D.h"
#include "GameObject.h"

struct Particle
{
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	float Life;

	Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};


class ParticleGenerator
{
public:
	ParticleGenerator(Shader shader, Texture2D texture, unsigned int amount);
	void Update(float dt, GameObject& object);
	void Draw();
	float spawnRate = 200.0f;     

private:
	float  _spawnAcc = 0.0f;      

	std::vector<Particle> particles;
	unsigned int amount;
	Shader shader;
	Texture2D texture;
	unsigned int VAO;
	void init();
	unsigned int firstUnusedParticle();
	void    respawnParticle(Particle& particle, const GameObject& object);

};

