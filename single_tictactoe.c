#include <stdio.h>
#include <stdlib.h>

char board[3][3]; // The tic-tac-toe board

// Function to initialize the board
void initializeBoard() {
	int i,j;
    for ( i = 0; i < 3; i++) {
        for ( j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to print the board
void printBoard() {
    printf(" %c | %c | %c\n", board[0][0], board[0][1], board[0][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[1][0], board[1][1], board[1][2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
}

// Function to check if a player has won
char checkWin() {
	int i;
    // Check rows, columns, and diagonals
    for (i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }
    
    return ' '; // No winner yet
}

// Function to check if the board is full
int isBoardFull() {
	int i,j;
    for ( i = 0; i < 3; i++) {
        for ( j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0; // Board is not full
            }
        }
    }
    return 1; // Board is full
}

// Function to evaluate the minimax value of a move
int minimax(int depth, int isMax) {
    char winner = checkWin();
    if (winner == 'X') {
        return -10 + depth;
    } else if (winner == 'O') {
        return 10 - depth;
    } else if (isBoardFull()) {
        return 0;
    }
    
    if (isMax) {
        int maxEval = -1000;
        int i,j;
        for ( i = 0; i < 3; i++) {
            for ( j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int eval = minimax(depth + 1, 0);
                    board[i][j] = ' ';
                    if (eval > maxEval) {
                        maxEval = eval;
                    }
                }
            }
        }
        return maxEval;
    } else {
        int minEval = 1000;
        int i,j;
        for ( i = 0; i < 3; i++) {
            for ( j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int eval = minimax(depth + 1, 1);
                    board[i][j] = ' ';
                    if (eval < minEval) {
                        minEval = eval;
                    }
                }
            }
        }
        return minEval;
    }
}

// Function to find the best move for the computer player
void findBestMove() {
    int bestEval = -1000;
    int bestMoveRow = -1;
    int bestMoveCol = -1;
    int i,j;
    for ( i = 0; i < 3; i++) {
        for ( j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int eval = minimax(0, 0);
                board[i][j] = ' ';
                if (eval > bestEval) {
                    bestEval = eval;
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }
    }
    
    board[bestMoveRow][bestMoveCol] = 'O';
}

int main() {
    int row, col;
    int currentPlayer = 1; // 1 for human, 0 for computer
    int moves = 0;

    initializeBoard();

    printf("Welcome to Tic-Tac-Toe against the computer!\n");

    while (1) {
        printBoard();

        if (currentPlayer == 1) {
            printf("Your move (row and column): ");
            scanf("%d %d", &row, &col);

            if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
                printf("Invalid move! Try again.\n");
                continue;
            }

            board[row][col] = 'X';
        } else {
            findBestMove();
        }

        moves++;

        char winner = checkWin();
        if (winner != ' ' || moves == 9) {
            printBoard();
            if (winner != ' ') {
                if (winner == 'X') {
                    printf("You win!\n");
                } else {
                    printf("Computer wins!\n");
                }
            } else {
                printf("It's a draw!\n");
            }
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 0 : 1;
    }

    return 0;
}

