#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Menu.h"

class Player;
class Map;
class Music;
class Level1;

const static int TRACK_X = 100;
const static int TRACK_Y = 300;
static const int TRACK_WIDTH = 600;
static const int TRACK_HEIGHT = 100;

extern int win_height;
extern int win_width;
extern int y;
extern int x;

extern SDL_Texture* background;
extern SDL_Window* win_window;
extern SDL_Renderer* render;
extern SDL_Texture* player;
extern TTF_Font* font;

extern SDL_DisplayMode displayMode;

extern bool isGameInitialized;
extern MenuState currentMenu;

void DeInit(int error);
void Init();
SDL_Texture* loadTextureFromFile(const char* filename, SDL_Renderer* render, SDL_Rect* rect);

#endif // GAME_H
