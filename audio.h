#ifndef _AUDIO__H
#define _AUDIO__H

#include <SDL_mixer.h>
#include <iostream>

struct Audio {
    Mix_Music* backgroundMusic = nullptr;
    Mix_Chunk* clickSound = nullptr;
    Mix_Chunk* winSound = nullptr;


    void init() {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cout << "SDL_mixer Error: " << Mix_GetError() << std::endl;
        }

        backgroundMusic = Mix_LoadMUS("music.mp3");
        if (!backgroundMusic) {
            std::cout << "Failed to load background music: " << Mix_GetError() << std::endl;
        }

        clickSound = Mix_LoadWAV("click.wav");
        if (!clickSound) {
            std::cout << "Failed to load click sound: " << Mix_GetError() << std::endl;
        }
        winSound = Mix_LoadWAV("win.wav");
        if (!winSound) {
            std::cout << "Failed to load win sound: " << Mix_GetError() << std::endl;
        }

    }

    void playMusic() {
        if (backgroundMusic != nullptr)
            Mix_PlayMusic(backgroundMusic, -1);  // Lặp vô hạn
    }
    void stopMusic() {
        Mix_HaltMusic();
    }

    void playClick() {
        if (clickSound != nullptr)
            Mix_PlayChannel(-1, clickSound, 0);
    }
    void playWinSound() {
        if (winSound) Mix_PlayChannel(-1, winSound, 0);
    }

    void quit() {
        Mix_FreeChunk(clickSound);
        Mix_FreeMusic(backgroundMusic);
        Mix_CloseAudio();
        Mix_FreeChunk(winSound);

    }
};

#endif

