#ifndef MENU_H
#define MENU_H

#include <SDL_ttf.h>

typedef enum {
    MENU_MAIN,
    MENU_SETTINGS,
    MENU_PLAY,
    GAME_PLAY
} MenuState;

void renderMenu(SDL_Renderer* renderer, TTF_Font* font, MenuState currentMenu, int win_width, int win_height);
void renderMenuItem(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
void handleMenuInput(MenuState* currentMenu, SDL_Event event, bool& isGameInitialized, int win_width, int win_height);

#endif // MENU_H
