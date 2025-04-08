#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include "logic.h"
#include "audio.h"
#include "ai.h"
using namespace std;

int playerScore = 0;
int aiScore = 0;

void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 &&
            (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

void processClick(int x, int y, Tictactoe& game) {
    int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
    game.move(clickedRow, clickedCol);
}

int main(int argc, char *argv[]) {
    Graphics graphics;
    graphics.init();
    graphics.loadFont("Roboto-Italic-VariableFont_wdth,wght.ttf", 32);

    Audio audio;
    audio.init();
    audio.playMusic();

    Tictactoe game;
    game.init();
    graphics.render(game);

    int x, y;
    SDL_Event event;
    bool quit = false;

    while (!quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                audio.playClick();
                processClick(x, y, game);
                graphics.render(game);

                char winner = game.checkWinner();
                if (winner != EMPTY_CELL) {
                    // X là người, O là máy
                    if (winner == X_CELL) playerScore++;
                    else if (winner == O_CELL) aiScore++;

                    graphics.prepareScene();
                    graphics.render(game);
                    graphics.drawText("Nguoi thang la " + std::string(1, winner), 300, 100, {255, 255, 255});
                    graphics.drawText("Ti so: May " + std::to_string(playerScore) + " - " + std::to_string(aiScore) + " Nguoi",
                                      300, 150, {200, 200, 0});
                    graphics.presentScene();

                    audio.stopMusic();
                    audio.playWinSound();
                    waitUntilKeyPressed();
                    game.init();
                    graphics.render(game);
                    audio.playMusic();
                }
                else if (game.nextMove == X_CELL) {
                    SDL_Delay(500);
                    aiMove(game);
                    graphics.render(game);

                    char aiWinner = game.checkWinner();
                    if (aiWinner != EMPTY_CELL) {
                        if (aiWinner == X_CELL) playerScore++;
                        else if (aiWinner == O_CELL) aiScore++;

                        graphics.prepareScene();
                        graphics.render(game);
                        graphics.drawText("Nguoi thang la " + std::string(1, aiWinner), 300, 100, {255, 255, 255});
                        graphics.drawText("Ti so: May " + std::to_string(playerScore) + " - " + std::to_string(aiScore) + " Nguoi",
                                          300, 150, {200, 200, 0});
                        graphics.presentScene();

                        audio.stopMusic();
                        audio.playWinSound();
                        waitUntilKeyPressed();
                        game.init();
                        graphics.render(game);
                        audio.playMusic();
                    }
                }
                break;
        }

        SDL_Delay(100);
    }

    audio.quit();
    graphics.quit();
    return 0;
}
