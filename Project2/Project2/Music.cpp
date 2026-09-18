#include "Music.h"
#include <algorithm>
#include <iostream>
#include "Saving.h"

using namespace std;

Music* Music::instance = nullptr;  // Initialize static pointer

Music::Music() : menuMusic1(nullptr), menuMusic2(nullptr), gameMusic(nullptr), loaded(false), currentTrackIndex(0), volume(MIX_MAX_VOLUME / 2), isMenuMusicPlaying(false), isGameMusicPlaying(false) {
    instance = this;  // Set the current object as the class instance

    // Load initial volume from config
    Config config("settings.cfg");
    if (config.load()) {
        volume = config.getInt("volume", MIX_MAX_VOLUME / 2);
    }
    Mix_VolumeMusic(volume); // Apply the loaded volume
}

Music::~Music() {
    stopMusic();
    if (menuMusic1 != nullptr) {
        Mix_FreeMusic(menuMusic1);
    }
    if (menuMusic2 != nullptr) {
        Mix_FreeMusic(menuMusic2);
    }
    if (gameMusic != nullptr) {
        Mix_FreeMusic(gameMusic);
    }

    // Save volume to config
    Config config("settings.cfg");
    config.setInt("volume", volume);
    config.save();
}

Music* Music::getInstance() {
    return instance; // Return the current class instance
}

void Music::loadMenuMusic(const char* filename1, const char* filename2) {
    menuMusic1 = Mix_LoadMUS(filename1);
    menuMusic2 = Mix_LoadMUS(filename2);
    if (menuMusic1 == nullptr || menuMusic2 == nullptr) {
        loaded = false;
    }
    else {
        loaded = true;
    }
}

void Music::loadGameMusic(const char* filename) {
    gameMusic = Mix_LoadMUS(filename);
    if (gameMusic == nullptr) {
        loaded = false;
    }
    else {
        loaded = true;
    }
}

void Music::playMenuMusic() {
    if (loaded && !isMenuMusicPlaying) { // Check if menu music is already playing
        Mix_VolumeMusic(volume); // Set volume before playing
        currentTrackIndex = 0;
        Mix_PlayMusic(menuMusic1, 1);
        Mix_HookMusicFinished(musicFinishedCallback);
        isMenuMusicPlaying = true;
        isGameMusicPlaying = false;
    }
}

void Music::playGameMusic() {
    if (loaded && !isGameMusicPlaying) { // Check if game music is already playing
        Mix_HookMusicFinished(nullptr); // Cancel any previously set callback
        Mix_VolumeMusic(volume);
        Mix_PlayMusic(gameMusic, 0);
        isGameMusicPlaying = true;
        isMenuMusicPlaying = false;
    }
}

void Music::stopMusic() {
    Mix_HaltMusic();
    isMenuMusicPlaying = false;
    isGameMusicPlaying = false;
}

bool Music::isLoaded() const {
    return loaded;
}

void Music::increaseVolume() {
    volume = min(volume + 8, MIX_MAX_VOLUME); // Increase volume by 8, but not above maximum
    Mix_VolumeMusic(volume); // Apply the new volume
}

void Music::decreaseVolume() {
    volume = max(volume - 8, 0); // Decrease volume by 8, but not below zero
    Mix_VolumeMusic(volume); // Apply the new volume
}

bool Music::isMusicPlaying() const {
    return Mix_PlayingMusic() != 0; // Check if music is playing
}

void Music::musicFinishedCallback() {
    if (instance != nullptr) {
        instance->currentTrackIndex = (instance->currentTrackIndex + 1) % 2;

        if (instance->currentTrackIndex == 0) {
            Mix_PlayMusic(instance->menuMusic1, 1);
        }
        else {
            Mix_PlayMusic(instance->menuMusic2, 1);
        }
    }
}

int Music::getVolume() const {
    return currentVolume;
}