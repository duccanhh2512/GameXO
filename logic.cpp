#include "logic.h"

void Tictactoe::init() {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = EMPTY_CELL;
    nextMove = O_CELL;
    while (!xMoves.empty()) xMoves.pop();
    while (!oMoves.empty()) oMoves.pop();
}

void Tictactoe::move(int row, int column) {
    if (row >= 0 && row < BOARD_SIZE &&
        column >= 0 && column < BOARD_SIZE &&
        board[row][column] == EMPTY_CELL)
    {
        board[row][column] = nextMove;

        if (nextMove == X_CELL) {
            xMoves.push({row, column});
            if (xMoves.size() > 3) {
                auto old = xMoves.front(); xMoves.pop();
                board[old.first][old.second] = EMPTY_CELL;
            }
        } else {
            oMoves.push({row, column});
            if (oMoves.size() > 3) {
                auto old = oMoves.front(); oMoves.pop();
                board[old.first][old.second] = EMPTY_CELL;
            }
        }

        nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;
    }
}

char Tictactoe::checkWinner() {
    for (int i = 0; i < BOARD_SIZE; ++i)
        if (board[i][0] != EMPTY_CELL &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return board[i][0];

    for (int j = 0; j < BOARD_SIZE; ++j)
        if (board[0][j] != EMPTY_CELL &&
            board[0][j] == board[1][j] &&
            board[1][j] == board[2][j])
            return board[0][j];

    if (board[0][0] != EMPTY_CELL &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return board[0][0];

    if (board[0][2] != EMPTY_CELL &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return board[0][2];

    return EMPTY_CELL;
}

