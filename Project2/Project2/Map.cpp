#include "Map.h"

Map* Map::instance = nullptr;

Map::Map(SDL_Renderer* render) : currentBackgroundIndex(0), back_tex(nullptr), second_back_tex(nullptr), level1(nullptr) {
    instance = this;
    back_tex = loadTextureFromFile("stage_backround.jpg", render, &back_rect);
    if (back_tex == nullptr) {
        std::cout << "Failed to load background texture" << std::endl;
    }
    level1 = new Level1(render, win_width, win_height); // Инициализация уровня
}

Map::~Map() {
    for (SDL_Texture* texture : backgrounds) {
        SDL_DestroyTexture(texture);
    }
    delete level1; // Освобождение памяти
}

void Map::loadBackground(const std::string& filename, SDL_Renderer* render) {
    SDL_Texture* texture = loadTextureFromFile(filename.c_str(), render, &back_rect);
    if (texture) {
        back_tex = texture;
    }
}

void Map::render(SDL_Renderer* render, int win_width, int win_height, MenuState currentMenu) {
    // Рендеринг статического фона
    SDL_Rect dst_rect = { 0, 0, win_width, win_height };
    SDL_RenderCopy(render, back_tex, nullptr, &dst_rect);

    // Рендеринг прокручивающегося фона только в GAME_PLAY
    if (currentMenu == GAME_PLAY && second_back_tex != nullptr) {
        int scrollSpeed = 1;
        int scrollOffset = static_cast<int>((SDL_GetTicks() / 10) % win_width);

        SDL_Rect dst_rect1 = { -scrollOffset, 0, win_width, win_height };
        SDL_Rect dst_rect2 = { win_width - scrollOffset, 0, win_width, win_height };

        SDL_RenderCopy(render, second_back_tex, nullptr, &dst_rect1);
        SDL_RenderCopy(render, second_back_tex, nullptr, &dst_rect2);

        level1->render(render, win_width, win_height); // Рендеринг уровня
    }
}

Map* Map::getInstance() {
    return instance;
}

void Map::changeBackground(const std::string& filename, SDL_Renderer* render) {
    back_tex = loadTextureFromFile(filename.c_str(), render, &back_rect);
}

void Map::GamePlayBackground(SDL_Renderer* render) {
    if (second_back_tex == nullptr) {
        second_back_tex = loadTextureFromFile("sky.jpg", render, &back_rect);
        std::cout << "GamePlayBackground loaded" << std::endl; // Отладка
    }
}

void Map::MenuBackground(SDL_Renderer* render) {
    changeBackground("stage_backround.jpg", render);
    if (second_back_tex != nullptr) {
        SDL_DestroyTexture(second_back_tex);
        second_back_tex = nullptr;
        std::cout << "MenuBackground loaded" << std::endl; // Отладка
    }
}

Level1* Map::getLevel1() const {
    return level1;
}

std::vector<SDL_Rect> Map::getObstacleRects() const {
    std::vector<SDL_Rect> rects;
    for (const Obstacle& obstacle : level1->getObstacles()) {
        rects.push_back(obstacle.getRect());
    }
    return rects;
}