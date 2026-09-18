#include "Menu.h"
#include "Music.h"
#include "Map.h"
#include "Level1.h"
#include "Player.h"
#include <SDL_mixer.h>

extern TTF_Font* font;
extern Level1* level;
extern Player* playerObject;

TTF_Font* font = nullptr;

void renderMenuItem(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    if (surface == nullptr) {
        // Handle error
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        // Handle error
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void handleMenuInput(MenuState* currentMenu, SDL_Event event, bool& isGameInitialized, int win_width, int win_height) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x = event.button.x;
        int y = event.button.y;

        int buttonX = win_width / 2 - 50;
        int buttonY = win_height / 2 - 100;

        if (*currentMenu == MENU_MAIN) {
            if (x >= buttonX && x <= buttonX + 100 && y >= buttonY && y <= buttonY + 42) {
                *currentMenu = MENU_PLAY;
            }
            else if (x >= buttonX && x <= buttonX + 100 && y >= buttonY + 70 && y <= buttonY + 70 + 42) {
                *currentMenu = MENU_SETTINGS;
            }
            else if (x >= buttonX && x <= buttonX + 100 && y >= buttonY + 140 && y <= buttonY + 140 + 42) {
                exit(1);
            }
        }
        else if (*currentMenu == MENU_SETTINGS) {
            if (x >= buttonX && x <= buttonX + 100 && y >= buttonY + 50 && y <= buttonY + 50 + 42) {
                Music::getInstance()->increaseVolume();
            }
            else if (x >= buttonX && x <= buttonX + 100 && y >= buttonY + 120 && y <= buttonY + 120 + 42) {
                Music::getInstance()->decreaseVolume();
            }
            else if (x >= buttonX && x <= buttonX + 100 && y >= buttonY + 190 && y <= buttonY + 190 + 42) {
                *currentMenu = MENU_MAIN;
            }
        }
        else if (*currentMenu == MENU_PLAY) {
            if (x >= buttonX && x <= buttonX + 100 && y >= buttonY && y <= buttonY + 42) {
                // Levels logic
            }
            else if (x >= buttonX && x <= buttonX + 100 && y >= buttonY + 50 && y <= buttonY + 50 + 42) {
                *currentMenu = GAME_PLAY;
                Music::getInstance()->playGameMusic();
                Map::getInstance()->GamePlayBackground(render);

                if (!isGameInitialized) {
                    if (level) delete level;
                    if (playerObject) delete playerObject;
                    level = new  Level1(render, win_width, win_height);
                    playerObject = new Player(render, level, win_width, win_height);
                    isGameInitialized = true;
                }
            }
            else if (x >= buttonX && x <= buttonX + 100 && y >= buttonY + 190 && y <= buttonY + 190 + 42) {
                *currentMenu = MENU_MAIN;
            }
        }
        else if (*currentMenu == GAME_PLAY) {
            if (x >= 20 && x <= 120 && y >= 20 && y <= 62) {
                *currentMenu = MENU_MAIN;
                Music::getInstance()->playMenuMusic();
                Map::getInstance()->MenuBackground(render);
                isGameInitialized = false;
            }
        }
    }
}

void renderMenu(SDL_Renderer* renderer, TTF_Font* font, MenuState currentMenu, int win_width, int win_height) {
    SDL_Color white = { 255, 255, 255, 255 };

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);

    int buttonX = win_width / 2 - 50;
    int buttonY = win_height / 2 - 100;

    if (currentMenu == MENU_MAIN) {
        SDL_Rect menuBackground = { win_width / 2 - 200, win_height / 2 - 150, 500, 300 };
        SDL_RenderFillRect(renderer, &menuBackground);

        renderMenuItem(renderer, font, "Play", buttonX, buttonY, white);
        renderMenuItem(renderer, font, "Settings", buttonX, buttonY + 70, white);
        renderMenuItem(renderer, font, "Quit", buttonX, buttonY + 140, white);
    }
    else if (currentMenu == MENU_SETTINGS) {
        SDL_Rect menuBackground = { win_width / 2 - 200, win_height / 2 - 150, 500, 300 };
        SDL_RenderFillRect(renderer, &menuBackground);

        renderMenuItem(renderer, font, "Setting", buttonX - 100, buttonY - 10, white);
        renderMenuItem(renderer, font, "Increase Volume", buttonX, buttonY + 50, white);
        renderMenuItem(renderer, font, "Decrease Volume", buttonX, buttonY + 120, white);
        renderMenuItem(renderer, font, "Back", buttonX, buttonY + 190, white);
    }
    else if (currentMenu == MENU_PLAY) {
        SDL_Rect menuBackground = { win_width / 2 - 200, win_height / 2 - 150, 500, 300 };
        SDL_RenderFillRect(renderer, &menuBackground);

        renderMenuItem(renderer, font, "Levels", buttonX - 100, buttonY - 10, white);
        renderMenuItem(renderer, font, "Jessi-Gum", buttonX, buttonY + 50, white);
        renderMenuItem(renderer, font, "Coming soon...", buttonX, buttonY + 120, white);
        renderMenuItem(renderer, font, "Back", buttonX, buttonY + 190, white);
    }
    else if (currentMenu == GAME_PLAY) {
        SDL_Rect cornerBackground = { 0, 0, 50, 100 };
        SDL_RenderFillRect(renderer, &cornerBackground);

        renderMenuItem(renderer, font, "...", 10, 10, white);
    }
}
