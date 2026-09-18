#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <vector>
#include "Level1.h"

class Player {
public:
    Player(SDL_Renderer* render, Level1* level, int win_width, int win_height);
    ~Player();

    void update(const std::vector<SDL_Rect>& obstacles);
    void render(SDL_Renderer* render);
    void handleEvent(const SDL_Event& e);
    void setFrame(int frame) { this->frame = frame; }

    bool shouldReturnToMainMenu() const { return returnToMainMenu; }

    SDL_Texture* getTexture() const { return player_tex; }
private:
    void applyGravity();
    void checkCollisions(const std::vector<SDL_Rect>& obstacles);

    SDL_Texture* player_tex;
    SDL_Rect player_rect;
    SDL_Rect collider;

    Level1* level1;

    int velocityY;
    int velocityX;
    int frame;
    int gravity;
    int jumpStrength;
    int moveSpeed;
    int win_width;
    int win_height;
    
    bool onGround;
    bool initialDescent;
    bool returnToMainMenu;
};

#endif // PLAYER_H
