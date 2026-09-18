#include "KeyboardController.h"

bool isup = false, isdown = false, isleft = false, isright = false;
double angle = 0;
int direction = DIR_RIGHT;

void handleKeyDown(SDL_Scancode scancode) {
    switch (scancode) {
    case SDL_SCANCODE_UP:
    case SDL_SCANCODE_SPACE:
        isup = true; 
        break;
    case SDL_SCANCODE_DOWN:
        isdown = true;
        break;
    case SDL_SCANCODE_RIGHT:
        isright = true; 
        direction = DIR_RIGHT;
        break;
    case SDL_SCANCODE_LEFT:
        isleft = true; 
        direction = DIR_LEFT;
        break;
    case SDL_SCANCODE_PAGEUP:
        angle += 5;
        break;
    case SDL_SCANCODE_PAGEDOWN:
        angle -= 5;
        break;
    }
}

void handleKeyUp(SDL_Scancode scancode) {
    switch (scancode) {
    case SDL_SCANCODE_UP:
    case SDL_SCANCODE_SPACE:
        isup = false;
        break;
    case SDL_SCANCODE_DOWN:
        isdown = false;
        break;
    case SDL_SCANCODE_RIGHT:
        isright = false;
        break;
    case SDL_SCANCODE_LEFT:
        isleft = false;
        break;
    }
}
