#include "Obstacle.h"

Obstacle::Obstacle(SDL_Texture* texture, int x, int y, int w, int h)
    : texture(texture), rect({ x, y, w, h }), collider({ x, y, w, h }) {}

SDL_Rect Obstacle::getRect() const {
    return rect;
}
