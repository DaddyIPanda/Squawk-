#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "Game.h"
#include "Menu.h"
#include "Level1.h"
#include "Obstacle.h"

class Map {
public:
    Map(SDL_Renderer* render);
    ~Map();

    void loadBackground(const std::string& filename, SDL_Renderer* render);
    void render(SDL_Renderer* render, int win_width, int win_height, MenuState currentMenu);
    void update();

    static Map* getInstance();

    void changeBackground(const std::string& filename, SDL_Renderer* render);
    void GamePlayBackground(SDL_Renderer* render);
    void MenuBackground(SDL_Renderer* render);

    SDL_Texture* getBackTex() const { return back_tex; }

    Level1* getLevel1() const;
    const std::vector<Obstacle>& getObstacles() const {
        return level1->getObstacles();
    }

    std::vector<SDL_Rect> getObstacleRects() const;

private:
    std::vector<SDL_Texture*> backgrounds;
    int currentBackgroundIndex;
    SDL_Texture* back_tex;
    SDL_Rect back_rect;
    SDL_Texture* second_back_tex;

    Level1* level1;

    static Map* instance;
};

#endif // MAP_H
