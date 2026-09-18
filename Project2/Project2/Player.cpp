#include "Player.h"
#include "Game.h"
#include <iostream>

Player::Player(SDL_Renderer* render, Level1* level, int win_width, int win_height)
    : velocityY(0), velocityX(0), onGround(false), level1(level), frame(0), gravity(1), jumpStrength(25), moveSpeed(15), win_width(win_width), win_height(win_height), initialDescent(true), returnToMainMenu(false) {
    player_tex = loadTextureFromFile("player.png", render, &player_rect);

    player_rect.w = 130;
    player_rect.h = 130;

    // Set player initial position above the screen for descent
    player_rect.x = win_width / 2 - player_rect.w / 2;
    player_rect.y = -player_rect.h; // Start above the screen
    collider = player_rect;
}

Player::~Player() {
    SDL_DestroyTexture(player_tex); // Clean up player texture
}

void Player::update(const std::vector<SDL_Rect>& obstacles) {
    if (initialDescent) {
        // Faster descent until landing on a platform
        velocityY = 5; // Increased descent rate
    }
    else {
        // Normal gravity effect
        velocityY += gravity;
    }

    collider.y += velocityY;
    checkCollisions(obstacles);

    collider.x += velocityX;

    if (collider.x < 0) {
        collider.x = 0;
    }
    if (collider.x + collider.w > win_width) {
        collider.x = win_width - collider.w;
    }
    if (collider.y < 0) {
        collider.y = 0;
    }
    if (collider.y + collider.h >= win_height) {
        collider.y = win_height - collider.h;
        onGround = true;
        velocityY = 0;
        returnToMainMenu = true; // Set flag to return to main menu
    }

    // Sync player rectangle with collider
    player_rect.y = collider.y;
    player_rect.x = collider.x;

    std::cout << "Player position: (" << player_rect.x << ", " << player_rect.y << "), VelocityY: " << velocityY << ", onGround: " << onGround << std::endl;
}

void Player::render(SDL_Renderer* render) {
    SDL_Rect src_rect = { 130 * frame, 0, 130, 130 };
    SDL_RenderCopy(render, player_tex, &src_rect, &player_rect); // Render player texture
}

void Player::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
        case SDLK_SPACE:
        case SDLK_UP:
            if (!initialDescent) {
                velocityY = -jumpStrength;
                std::cout << "Jump initiated!" << std::endl;
            }
            break;
        case SDLK_LEFT:
            velocityX = -moveSpeed;
            break;
        case SDLK_RIGHT:
            velocityX = moveSpeed;
            break;
        }
    }

    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
        case SDLK_RIGHT:
            velocityX = 0;
            break;
        }
    }
}

void Player::applyGravity() {
    if (!initialDescent) {
        velocityY += gravity;
    }
}

void Player::checkCollisions(const std::vector<SDL_Rect>& obstacles) {
    onGround = false;
    for (const SDL_Rect& obstacle : obstacles) {
        if (SDL_HasIntersection(&collider, &obstacle)) {
            if (velocityY >= 0) { // Falling or stationary
                int playerBottom = collider.y + collider.h;
                int obstacleTop = obstacle.y;
                int playerRight = collider.x + collider.w;
                int playerLeft = collider.x;
                int obstacleRight = obstacle.x + obstacle.w;
                int obstacleLeft = obstacle.x;

                if (playerRight > obstacleLeft && playerLeft < obstacleRight) {
                    if (playerBottom > obstacleTop && collider.y < obstacleTop) {
                        collider.y = obstacleTop - collider.h;
                        onGround = true;
                        velocityY = 0; // Reset vertical velocity when hitting the ground
                        initialDescent = false; // End initial descent on first platform collision
                        std::cout << "Landed on platform at y: " << obstacle.y << std::endl;
                    }
                }
            }
            break;
        }
    }

    // Check collision with arrows
    for (const SDL_Rect& obstacle : obstacles) {
        if (SDL_HasIntersection(&collider, &obstacle)) {
            returnToMainMenu = true;
            break;
        }
    }
}