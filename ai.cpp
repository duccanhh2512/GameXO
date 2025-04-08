#include "ai.h"

void aiMove(Tictactoe& game) {
    if (game.nextMove != X_CELL) return;

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (game.board[i][j] == EMPTY_CELL) {
                game.board[i][j] = X_CELL;
                if (game.checkWinner() == X_CELL) {
                    game.board[i][j] = EMPTY_CELL;
                    game.move(i, j);
                    return;
                }
                game.board[i][j] = EMPTY_CELL;
            }

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (game.board[i][j] == EMPTY_CELL) {
                game.board[i][j] = O_CELL;
                if (game.checkWinner() == O_CELL) {
                    game.board[i][j] = EMPTY_CELL;
                    game.move(i, j);
                    return;
                }
                game.board[i][j] = EMPTY_CELL;
            }

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            if (game.board[i][j] == EMPTY_CELL) {
                game.move(i, j);
                return;
            }
}

