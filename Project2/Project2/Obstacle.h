#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>

class Obstacle {
public:
    Obstacle(SDL_Texture* texture, int x, int y, int w, int h); // Конструктор с текстурой препятствия
    SDL_Rect getRect() const;

    SDL_Texture* texture; // Член для хранения текстуры препятствия
    SDL_Rect rect;        // Член для хранения прямоугольника препятствия
    SDL_Rect collider;    // Член для хранения коллизионной области препятствия
};

#endif // OBSTACLE_H
