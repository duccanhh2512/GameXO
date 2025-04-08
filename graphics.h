#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "logic.h"
#include <SDL_ttf.h>
#include <string>

struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;

    SDL_Texture *cellEmpty, *cellX, *cellO;
    SDL_Texture *background = nullptr;
    TTF_Font* font = nullptr;

    void init() {
        initSDL();
        cellEmpty = loadTexture("cell_empty.png");
        cellX = loadTexture("cell_x.png");
        cellO = loadTexture("cell_o.png");
        background = loadTexture("background.png");
    }

    void render(const Tictactoe& game) {
        prepareScene(background);

        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) {
                int x = BOARD_X + j * CELL_SIZE;
                int y = BOARD_Y + i * CELL_SIZE;
                switch (game.board[i][j]) {
                    case EMPTY_CELL: renderTexture(cellEmpty, x, y); break;
                    case X_CELL: renderTexture(cellX, x, y); break;
                    case O_CELL: renderTexture(cellO, x, y); break;
                };
            };

        presentScene();
    }

	void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

	void initSDL() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit("SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

	void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        if (background)
            SDL_RenderCopy(renderer, background, NULL, NULL);
    }

    void prepareScene()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    void loadFont(const char* fontPath, int fontSize) {
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

    void quit()
    {
        SDL_DestroyTexture(cellEmpty);
        cellEmpty = nullptr;
        SDL_DestroyTexture(cellX);
        cellX = nullptr;
        SDL_DestroyTexture(cellO);
        cellO = nullptr;

        if (background) {
            SDL_DestroyTexture(background);
            background = nullptr;
        }

        if (font) {
            TTF_CloseFont(font);
            font = nullptr;
        }

        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        TTF_Quit();
    }
};

#endif // _GRAPHICS__H
