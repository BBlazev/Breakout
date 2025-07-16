![Breakout](https://github.com/user-attachments/assets/d9943643-534e-44a7-b7b8-8e8ad0b50f4f)
# Breakout Game

A modern implementation of the classic Breakout arcade game built with C++ and OpenGL, featuring advanced graphics effects, power-ups, and dynamic gameplay mechanics.

## Features

### Core Gameplay
- **Classic Breakout Mechanics**: Control a paddle to bounce a ball and destroy all breakable bricks
- **Multiple Levels**: Four distinct levels with increasing difficulty
- **Progressive Speed System**: Ball automatically speeds up over time for increased challenge
- **Collision Detection**: Precise physics-based collision system for ball-paddle and ball-brick interactions

### Power-Up System
- **Speed Boost**: Increases paddle movement speed
- **Sticky Ball**: Ball sticks to paddle on contact for strategic positioning
- **Pass-Through**: Ball passes through breakable bricks without bouncing
- **Paddle Size Increase**: Temporarily enlarges the paddle for easier ball control
- **Confuse Effect**: Inverts screen colors for added challenge
- **Chaos Effect**: Applies visual distortion effects

### Visual Effects
- **Particle System**: Dynamic particle trail following the ball
- **Post-Processing Effects**: 
  - Screen shake on solid brick collisions
  - Chaos and confuse visual filters
  - Multi-sample anti-aliasing (MSAA)
- **Brick Shake Animation**: Periodic brick shaking effect for visual flair
- **Dynamic Lighting**: Color-coded bricks with smooth rendering

### Technical Features
- **Modern OpenGL**: Shader-based rendering pipeline
- **Resource Management**: Efficient texture and shader loading system
- **Modular Architecture**: Clean separation of game logic, rendering, and physics
- **Level Loading**: External level file support for easy level creation

## Brick Types

- **Solid Bricks** (Gray): Indestructible barriers that cause screen shake
- **Breakable Bricks**: Color-coded destroyable blocks
  - Green (Code 2)
  - Cyan (Code 3)  
  - Magenta (Code 4)
  - Yellow (Code 5)

## Controls

- **A/Left Arrow**: Move paddle left
- **D/Right Arrow**: Move paddle right
- **Spacebar**: Release ball from paddle

## Technical Requirements

### Dependencies
- OpenGL 3.3+
- GLFW (Window management)
- GLAD (OpenGL loader)
- GLM (Mathematics library)
- stb_image (Texture loading)

### Build Requirements
- C++11 or later
- OpenGL-compatible graphics driver


## Game Mechanics

### Ball Physics
- **Dynamic Speed**: Ball speed increases every 10 seconds by 4% (capped at 600 units/second)
- **Collision Response**: Realistic bouncing with velocity preservation
- **Boundary Collision**: Ball bounces off screen edges (top, left, right)
- **Paddle Interaction**: Ball direction influenced by paddle contact point

### Power-Up Spawning
Power-ups have different spawn rates when bricks are destroyed:
- Speed Boost: 2.5% chance
- Sticky Ball: 2.2% chance  
- Pass-Through: 2.0% chance
- Paddle Size Increase: 2.7% chance
- Confuse Effect: 5.0% chance
- Chaos Effect: 5.0% chance

### Level Progression
- Complete a level by destroying all non-solid bricks
- Automatic progression to next level
- Game won after completing all four levels
- Level reset on ball loss

## Future Enhancements

- [ ] Sound effects and background music
- [ ] High score system
- [ ] Additional power-up types
- [ ] Customizable controls
- [ ] Level editor


## Acknowledgments

- Inspired by the classic Atari Breakout game
- Built following modern OpenGL best practices
- Uses learnopengl.com tutorials as reference
