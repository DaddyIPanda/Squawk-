#ifndef MUSIC_H
#define MUSIC_H

#include <SDL_mixer.h>

class Music {
public:
    Music();
    ~Music();

    void loadMenuMusic(const char* filename1, const char* filename2);
    void loadGameMusic(const char* filename);

    void playMenuMusic();
    void playGameMusic();
    void stopMusic();
    void increaseVolume();
    void decreaseVolume();

    bool isLoaded() const;
    bool isMusicPlaying() const;

    static Music* getInstance();
    int getVolume() const;

private:
    static void musicFinishedCallback();

    Mix_Music* menuMusic1;
    Mix_Music* menuMusic2;
    Mix_Music* gameMusic;

    bool loaded;
    int currentTrackIndex;
    int volume; 
    bool isMenuMusicPlaying;
    bool isGameMusicPlaying;

    static Music* instance; 
    int currentVolume;
};

#endif // MUSIC_H
