#pragma once

#include "GameLevel.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "PowerUp.h"



const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY(500.0f);

const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.5f;

enum GameState {

	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN

};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
typedef std::tuple<bool, Direction, glm::vec2> Collision; 

class Game
{
public:

	GameState State;
	bool Keys[1024];
	unsigned int Width, Height;

	float SpeedUpInterval = 6.0f;    
	float SpeedUpFactor = 1.08f;    
	float SpeedUpTimer = 0.0f;    

	float ElapsedTime = 0.0f;   
	bool  BlocksShouldShake = false;
	float BlockShakeAmount = 3.0f;
	
	std::vector<PowerUp> PowerUps;
	std::vector<GameLevel> Levels;

	unsigned int Level;

	unsigned int   PostProcessFBO;
	unsigned int   PostProcessTexture;
	unsigned int   PostProcessRBO;
	unsigned int   ScreenVAO;

	Game(unsigned int width, unsigned int height);
	~Game();

	void Init();
	void DoCollisions();
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
	void ResetLevel();
	void ResetPlayer();
	void SpawnPowerUps(GameObject& block);
	void UpdatePowerUps(float dt);
};

