#pragma once

#include "GameObject.h"

class BallObject : public GameObject
{
public:

    float   Radius;
    bool    Stuck;
    bool Sticky, PassThrough;

    float     BaseSpeed = 300.0f;  
    float     SpeedFactor = 1.0f;     
    float     SpeedTimer = 0.0f;

    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);
    glm::vec2 Move(float dt, unsigned int window_width);
    void      Reset(glm::vec2 position, glm::vec2 velocity);



};

