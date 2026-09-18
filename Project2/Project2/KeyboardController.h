#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include <SDL.h>

extern bool isup, isdown, isleft, isright;
extern double angle;
extern int direction;
extern SDL_Event ev;

constexpr auto DIR_RIGHT = 1;
constexpr auto DIR_LEFT = 2;

void handleKeyDown(SDL_Scancode scancode);
void handleKeyUp(SDL_Scancode scancode);

#endif // KEYBOARDCONTROLLER_H
