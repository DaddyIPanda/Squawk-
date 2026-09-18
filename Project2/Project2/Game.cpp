#include "Game.h"
#include "Music.h"
#include "Map.h"
#include "Player.h"
#include "KeyboardController.h"
#include "Menu.h"
#include "Level1.h"
#include "Saving.h"

using namespace std;

int win_width = 1500;
int win_height = 499;
int x = 78, y = 750;

SDL_Texture* background = nullptr;
SDL_Window* win_window = nullptr;
SDL_Renderer* render = nullptr;
SDL_Texture* player = nullptr;

SDL_DisplayMode displayMode;

Music music;

bool isGameInitialized = false;
Level1* level = nullptr;
Player* playerObject = nullptr;
MenuState currentMenu = MENU_MAIN;

void DeInit(int error) {
    if (render != NULL) SDL_DestroyRenderer(render);
    if (win_window != NULL) SDL_DestroyWindow(win_window);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    exit(error);
}

void Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Couldn't init SDL. Error: " << SDL_GetError() << "\n";
        system("pause");
        DeInit(1);
    }

    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0) {
        cout << "Couldn't get desktop display mode. Error: " << SDL_GetError() << "\n";
        system("pause");
        DeInit(1);
    }
    win_width = displayMode.w;
    win_height = displayMode.h;

    win_window = SDL_CreateWindow("Squawk!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);

    if (win_window == NULL) {
        cout << "Couldn't create window. Error: " << SDL_GetError() << "\n";
        system("pause");
        DeInit(1);
    }

    render = SDL_CreateRenderer(win_window, -1, SDL_RENDERER_ACCELERATED);
    if (render == NULL) {
        cout << "Couldn't create renderer. Error: " << SDL_GetError() << "\n";
        system("pause");
        DeInit(1);
    }

    int res;
    if ((res = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) == 0) {
        cout << "Couldn't init SDL_Image. Error: " << SDL_GetError() << "\n";
        system("pause");
        DeInit(1);
    }

    if (res & IMG_INIT_PNG) cout << "Initializing PNG library" << "\n"; else cout << "Couldn't init PNG library. Error: " << SDL_GetError() << "\n";
    if (res & IMG_INIT_JPG) cout << "Initializing JPG library" << "\n"; else cout << "Couldn't init JPG library. Error: " << SDL_GetError() << "\n";

    if (TTF_Init() < 0) {
        cout << "Couldn't initialize SDL_ttf. Error: " << TTF_GetError() << "\n";
        system("pause");
        DeInit(1);
    }

    font = TTF_OpenFont("Machine BT.ttf", 42);
    if (font == nullptr) {
        cout << "Failed to load font. Error: " << TTF_GetError() << "\n";
        system("pause");
        DeInit(1);
    }
    else {
        cout << "Loading font\n";
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024) < 0) {
        cout << "Couldn't initialize SDL_mixer. Error: " << Mix_GetError() << "\n";
        system("pause");
        DeInit(1);
    }

    // Initialize music and player
    music.loadMenuMusic("lady-of-the-80.mp3", "reflected-light.mp3");
    music.loadGameMusic("1698295066_jessi_gum.mp3");

    if (!music.isLoaded()) {
        cout << "Failed to load music. Error: " << Mix_GetError() << "\n";
        system("pause");
        DeInit(1);
    }
    else {
        cout << "Loading menu music\n";
        music.playMenuMusic();
    }
}

SDL_Texture* loadTextureFromFile(const char* filename, SDL_Renderer* render, SDL_Rect* rect) {
    SDL_Surface* surface = IMG_Load(filename);
    if (surface == nullptr) {
        cout << "Couldn't load image " << filename << ". Error: " << IMG_GetError() << "\n";
        system("pause");
        DeInit(1);
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
    if (texture == nullptr) {
        cout << "Couldn't create texture from surface. Error: " << SDL_GetError() << "\n";
        SDL_FreeSurface(surface);
        system("pause");
        DeInit(1);
        return nullptr;
    }

    if (rect != nullptr) {
        *rect = { 0, 0, surface->w, surface->h };
    }

    SDL_FreeSurface(surface);
    return texture;
}

void resetGame() {
    if (level) delete level;
    if (playerObject) delete playerObject;
    level = new Level1(render, win_width, win_height);
    playerObject = new Player(render, level, win_width, win_height);
    isGameInitialized = true;
}

int main(int argc, char* argv[]) {
    Init();

    bool isRunning = true;
    SDL_Event ev;

    int delta = 10;
    SDL_Rect dst_rect = { 100, 300, 130, 130 }; // Player initial position and size
    int frame = 0;
    int frame_count = 4;
    int cur_frametime = 0;
    int max_frametime = 1000 / 8;

    Map mapObject(render);

    int newtime;
    int lasttime = static_cast<int>(SDL_GetTicks64());
    int dt = 0;

    bool animate = false;

    while (isRunning) {
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_WINDOWEVENT:
                if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    win_width = ev.window.data1;
                    win_height = ev.window.data2;
                }
                break;
            case SDL_KEYDOWN:
                handleKeyDown(ev.key.keysym.scancode);
                break;
            case SDL_KEYUP:
                handleKeyUp(ev.key.keysym.scancode);
                break;
            }

            if (currentMenu == GAME_PLAY && !isGameInitialized) {
                resetGame();
            }

            if (currentMenu == GAME_PLAY && isGameInitialized) {
                playerObject->handleEvent(ev);
            }

            handleMenuInput(&currentMenu, ev, isGameInitialized, win_width, win_height);
        }

        newtime = static_cast<int>(SDL_GetTicks64());
        dt = newtime - lasttime;
        lasttime = newtime;
        animate = isup || isdown || isright || isleft;

        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderClear(render);

        mapObject.render(render, win_width, win_height, currentMenu);

        if (currentMenu == GAME_PLAY && isGameInitialized) {
            level->update(0); // Update level for scrolling platforms
            level->render(render, win_width, win_height); // Render level before player
            if (animate) {
                cur_frametime += dt;
                if (cur_frametime >= max_frametime) {
                    cur_frametime -= max_frametime;
                    frame = (frame + 1) % frame_count;
                    playerObject->setFrame(frame); // Update frame in playerObject
                }
            }
            playerObject->update(level->getObstacleRects());
            playerObject->render(render);
            if (playerObject->shouldReturnToMainMenu()) {
                currentMenu = MENU_MAIN;
                Music::getInstance()->playMenuMusic();
                isGameInitialized = false;
            }
        }

        renderMenu(render, font, currentMenu, win_width, win_height);


        SDL_RenderPresent(render);

        SDL_Delay(20);
    }

    SDL_DestroyTexture(playerObject->getTexture());
    SDL_DestroyTexture(mapObject.getBackTex());
    
    // Save game settings
    Config config("settings.cfg");
    config.setInt("volume", music.getVolume());
    config.save();

    DeInit(0);
    return 0;
}
