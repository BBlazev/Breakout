#include "GameLevel.h"

#include <sstream>
#include <fstream>
#include <cstdlib> 
void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    this->Bricks.clear();

    unsigned int tileCode;
    GameLevel level;

    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;

    if (fstream) {

        while (std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);


    }

}

void GameLevel::Draw(SpriteRenderer& renderer, bool shake, float amount)
{
    for (GameObject& tile : this->Bricks)
    {
        if (tile.Destroyed) continue;

        // save original
        glm::vec2 origPos = tile.Position;

        if (shake)
        {
            float ox = ((rand() % 100) / 100.0f - 0.5f) * amount;
            float oy = ((rand() % 100) / 100.0f - 0.5f) * amount;
            tile.Position += glm::vec2(ox, oy);
        }

        tile.Draw(renderer);

        // restore
        tile.Position = origPos;
    }
}
bool GameLevel::IsCompleted()
{
    for (GameObject& tile : this->Bricks)
        if (!tile.IsSolid && !tile.Destroyed)
            return false;
    return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();

    float unit_width = levelWidth / static_cast<float>(width);
    float unit_height = levelHeight / static_cast<float>(height);

    const float s = 0.8f;

    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            unsigned int tileCode = tileData[y][x];
            if (tileCode == 0) continue;  

            glm::vec2 cellPos = { unit_width * x, unit_height * y };
            glm::vec2 brickSize = { unit_width * s, unit_height * s };
            glm::vec2 brickPos = {
                cellPos.x + (unit_width - brickSize.x) * 0.5f,
                cellPos.y + (unit_height - brickSize.y) * 0.5f
            };

            if (tileCode == 1) 
            {
                GameObject obj(
                    brickPos, brickSize,
                    ResourceManager::GetTexture("block_solid"),
                    glm::vec3(0.8f, 0.8f, 0.7f)
                );
                obj.IsSolid = true;
                this->Bricks.push_back(obj);
            }
            else 
            {
                glm::vec3 color = glm::vec3(1.0f);

                if (tileCode == 2)      color = { 0.0f, 1.0f, 0.0f };  // green
                else if (tileCode == 3) color = { 0.0f, 1.0f, 1.0f };  // cyan
                else if (tileCode == 4) color = { 1.0f, 0.0f, 1.0f };  // magenta
                else if (tileCode == 5) color = { 1.0f, 1.0f, 0.0f };  // yellow



                this->Bricks.emplace_back(
                    brickPos, brickSize,
                    ResourceManager::GetTexture("block"),
                    color
                );
            }
        }
    }
}