#ifndef _FONT__H
#define _FONT__H

#include <SDL_ttf.h>
#include <string>

struct FontRenderer {
    TTF_Font* font = nullptr;
    SDL_Renderer* renderer;

    void init(SDL_Renderer* ren, const char* fontPath, int fontSize) {
        renderer = ren;
        if (TTF_Init() < 0) {
            SDL_Log("TTF_Init Error: %s", TTF_GetError());
        }
        font = TTF_OpenFont(fontPath, fontSize);
        if (!font) {
            SDL_Log("Failed to load font: %s", TTF_GetError());
        }
    }

    void drawText(const std::string& message, int x, int y, SDL_Color color) {
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, message.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect destRect = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void quit() {
        if (font) {
            TTF_CloseFont(font);
            font = nullptr;
        }
        TTF_Quit();
    }
};

#endif

