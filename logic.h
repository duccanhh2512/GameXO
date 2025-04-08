#ifndef _LOGIC__H
#define _LOGIC__H

#define BOARD_SIZE 3
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'

#include <queue>
#include <utility>

struct Tictactoe {
    char board[BOARD_SIZE][BOARD_SIZE];
    char nextMove = O_CELL;
    std::queue<std::pair<int, int>> xMoves;
    std::queue<std::pair<int, int>> oMoves;

    void init();
    void move(int row, int column);
    char checkWinner();
};

#endif
