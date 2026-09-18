#ifndef LEVEL1_H
#define LEVEL1_H

#include <SDL.h>
#include <vector>
#include "Obstacle.h"
#include "Game.h"

class Level1 {
public:
    Level1(SDL_Renderer* renderer, int win_width, int win_height);
    ~Level1();
    
    void loadObstacles(SDL_Renderer* render);
    void update(int scrollOffset);
    void render(SDL_Renderer* render, int win_width, int win_height);
    void reset();
    bool checkCollision(const SDL_Rect& playerRect) const;
    const std::vector<Obstacle>& getObstacles() const;
    std::vector<SDL_Rect> getObstacleRects() const;

private:
    SDL_Renderer* renderer;
    int win_width;
    int win_height;
    int scrollSpeed;
    int platformWidth;
    int platformHeight;
    
    std::vector<Obstacle> obstacles;

    SDL_Texture* arrowTexture;
    std::vector<Obstacle> arrows;

    void resetPlatform(int index);
    void updateArrows();
    void resetArrow(Obstacle& arrow);
};

#endif // LEVEL1_H
