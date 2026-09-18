#include "Level1.h"
#include <iostream>
#include <SDL_image.h>
#include <cstdlib>

const int NUM_PLATFORMS = 6; // Number of platforms
const int PLATFORM_SPACING = 150; // Vertical distance between platforms

Level1::Level1(SDL_Renderer* render, int win_width, int win_height)
    : renderer(render), win_width(win_width), win_height(win_height), scrollSpeed(10) {
    loadObstacles(render);
}

Level1::~Level1() {
    for (Obstacle& obstacle : obstacles) {
        SDL_DestroyTexture(obstacle.texture);
    }
    for (Obstacle& arrow : arrows) {
        SDL_DestroyTexture(arrow.texture);
    }
}

void Level1::loadObstacles(SDL_Renderer* render) {
    SDL_Texture* texture = IMG_LoadTexture(render, "Platform.png");
    if (texture == nullptr) {
        std::cout << "Failed to load obstacle texture: " << IMG_GetError() << std::endl;
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &platformWidth, &platformHeight);

    // Reduce platform size by half
    platformWidth /= 2;
    platformHeight /= 2;

    // Calculate positions based on the window height
    int yPositions[2] = { win_height - (platformHeight + 50), win_height - (platformHeight + 200) }; // Adjust as needed

    // Create ladder-like arrangement of platforms
    int x = win_width + platformWidth;
    int yIndex = 0; // Start from the first position in yPositions

    for (int i = 0; i < NUM_PLATFORMS; ++i) {
        int y = yPositions[yIndex];
        obstacles.emplace_back(texture, x, y, platformWidth, platformHeight);
        std::cout << "Platform created at x: " << x << ", y: " << y << std::endl;

        // Move x to the right and toggle y position between the two possible positions
        x += platformWidth + PLATFORM_SPACING;
        yIndex = (yIndex + 1) % 2;
    }

    // Load arrow texture
    arrowTexture = IMG_LoadTexture(render, "arrow(totheleft).jpg");
    if (arrowTexture == nullptr) {
        std::cout << "Failed to load arrow texture: " << IMG_GetError() << std::endl;
        return;
    }

    // Create initial arrows
    for (int i = 0; i < NUM_PLATFORMS; ++i) {
        int arrowX = win_width + rand() % 200 + 50; // Randomize initial arrow position
        int arrowY = yPositions[i % 2] - 20; // Position arrow slightly above the platform
        arrows.emplace_back(arrowTexture, arrowX, arrowY, 50, 20); // Arrow dimensions 50x20
    }
}

void Level1::update(int scrollOffset) {
    for (size_t i = 0; i < obstacles.size(); ++i) {
        obstacles[i].rect.x -= scrollSpeed;

        if (obstacles[i].rect.x + obstacles[i].rect.w < 0) {
            // Reset a single platform to the right side of the screen in the correct position in the ladder
            resetPlatform(i);
        }
    }

    updateArrows(); // Update arrow positions
}

void Level1::updateArrows() {
    for (auto& arrow : arrows) {
        arrow.rect.x -= scrollSpeed * 2; // Arrows move faster than platforms

        if (arrow.rect.x + arrow.rect.w < 0) {
            // Reset the arrow to the right side of the screen
            resetArrow(arrow);
        }
    }
}

void Level1::resetArrow(Obstacle& arrow) {
    int yPositions[2] = { win_height - (platformHeight + 50), win_height - (platformHeight + 200) };
    int yIndex = rand() % 2;
    arrow.rect.x = win_width + rand() % 200 + 50;
    arrow.rect.y = yPositions[yIndex] - 20;
}

void Level1::resetPlatform(int index) {
    // Calculate the new position based on the index and ladder logic
    int x = win_width + platformWidth;
    int yPositions[2] = { win_height - (platformHeight + 50), win_height - (platformHeight + 200) }; // Adjust as needed
    int yIndex = index % 2; // Determine the y position based on the index

    obstacles[index].rect.x = x;
    obstacles[index].rect.y = yPositions[yIndex];
    std::cout << "Platform reset to x: " << obstacles[index].rect.x << ", y: " << obstacles[index].rect.y << std::endl;
}

void Level1::render(SDL_Renderer* render, int win_width, int win_height) {
    for (const Obstacle& obstacle : obstacles) {
        SDL_RenderCopy(render, obstacle.texture, nullptr, &obstacle.rect);
    }

    // Render arrows
    for (const Obstacle& arrow : arrows) {
        SDL_RenderCopy(render, arrow.texture, nullptr, &arrow.rect);
    }
}

void Level1::reset() {
    // Reset the positions to the initial ladder-like arrangement
    int x = win_width + platformWidth;
    int yPositions[2] = { win_height - (platformHeight + 50), win_height - (platformHeight + 200) }; // Adjust as needed
    int yIndex = 0; // Start from the first position in yPositions

    for (size_t i = 0; i < obstacles.size(); ++i) {
        int y = yPositions[yIndex];
        obstacles[i].rect.x = x;
        obstacles[i].rect.y = y;

        // Move x to the right and toggle y position between the two possible positions
        x += platformWidth + PLATFORM_SPACING;
        yIndex = (yIndex + 1) % 2;
    }

    // Reset arrows
    for (auto& arrow : arrows) {
        resetArrow(arrow);
    }
}

bool Level1::checkCollision(const SDL_Rect& playerRect) const {
    for (const Obstacle& obstacle : obstacles) {
        if (SDL_HasIntersection(&playerRect, &obstacle.rect)) {
            return true;
        }
    }

    // Check collision with arrows
    for (const Obstacle& arrow : arrows) {
        if (SDL_HasIntersection(&playerRect, &arrow.rect)) {
            return true;
        }
    }

    return false;
}

const std::vector<Obstacle>& Level1::getObstacles() const {
    return obstacles;
}

std::vector<SDL_Rect> Level1::getObstacleRects() const {
    std::vector<SDL_Rect> rects;
    for (const Obstacle& obstacle : obstacles) {
        rects.push_back(obstacle.rect);
    }
    return rects;
}
