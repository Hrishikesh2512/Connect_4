#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for player
typedef struct {
    char name[50];
    char symbol;
} Player;

// Structure for the game board
typedef struct {
    int rows;
    int cols;
    char **grid;  // dynamically allocated 2D array
} GameBoard;

// Function to create a new board dynamically
GameBoard* createBoard(int rows, int cols) {
    GameBoard *board = (GameBoard*) malloc(sizeof(GameBoard));
    board->rows = rows;
    board->cols = cols;

    board->grid = (char**) malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++)
        board->grid[i] = (char*) malloc(cols * sizeof(char));

    // fill with dots
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            board->grid[i][j] = '.';

    return board;
}

// Function to free the board
void freeBoard(GameBoard *board) {
    for (int i = 0; i < board->rows; i++)
        free(board->grid[i]);
    free(board->grid);
    free(board);
}

// Function to display the board
void displayBoard(GameBoard *board) {
    printf("\n");
    for (int i = 0; i < board->rows; i++) {
        for (int j = 0; j < board->cols; j++)
            printf("%c ", board->grid[i][j]);
        printf("\n");
    }
    for (int i = 0; i < board->cols; i++)
        printf("%d ", i);
    printf("\n\n");
}

// Function to drop a disc
int dropDisc(GameBoard *board, int col, char symbol) {
    if (col < 0 || col >= board->cols)
        return 0;

    for (int i = board->rows - 1; i >= 0; i--) {
        if (board->grid[i][col] == '.') {
            board->grid[i][col] = symbol;
            return 1;
        }
    }
    return 0; // column full
}

// Function to check for winner
int checkWinner(GameBoard *board, char symbol) {
    int r, c;

    // horizontal
    for (r = 0; r < board->rows; r++)
        for (c = 0; c < board->cols - 3; c++)
            if (board->grid[r][c] == symbol &&
                board->grid[r][c+1] == symbol &&
                board->grid[r][c+2] == symbol &&
                board->grid[r][c+3] == symbol)
                return 1;

    // vertical
    for (r = 0; r < board->rows - 3; r++)
        for (c = 0; c < board->cols; c++)
            if (board->grid[r][c] == symbol &&
                board->grid[r+1][c] == symbol &&
                board->grid[r+2][c] == symbol &&
                board->grid[r+3][c] == symbol)
                return 1;

    // diagonal down-right
    for (r = 0; r < board->rows - 3; r++)
        for (c = 0; c < board->cols - 3; c++)
            if (board->grid[r][c] == symbol &&
                board->grid[r+1][c+1] == symbol &&
                board->grid[r+2][c+2] == symbol &&
                board->grid[r+3][c+3] == symbol)
                return 1;

    // diagonal up-right
    for (r = 3; r < board->rows; r++)
        for (c = 0; c < board->cols - 3; c++)
            if (board->grid[r][c] == symbol &&
                board->grid[r-1][c+1] == symbol &&
                board->grid[r-2][c+2] == symbol &&
                board->grid[r-3][c+3] == symbol)
                return 1;

    return 0;
}

// Function to check if board is full
int isFull(GameBoard *board) {
    for (int i = 0; i < board->rows; i++)
        for (int j = 0; j < board->cols; j++)
            if (board->grid[i][j] == '.')
                return 0;
    return 1;
}

// Main function
int main() {
    printf("\n=== CONNECT IV ===\n");

    Player p1, p2;
    printf("Enter name of Player 1: ");
    scanf("%s", p1.name);
    p1.symbol = 'X';

    printf("Enter name of Player 2: ");
    scanf("%s", p2.name);
    p2.symbol = 'O';

    GameBoard *board = createBoard(6, 7);

    int turn = 0, col;
    int gameOver = 0;

    while (!gameOver) {
        displayBoard(board);
        Player current = (turn % 2 == 0) ? p1 : p2;

        printf("%s's turn (%c). Choose column (0-6): ", current.name, current.symbol);
        scanf("%d", &col);

        if (!dropDisc(board, col, current.symbol)) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        if (checkWinner(board, current.symbol)) {
            displayBoard(board);
            printf("\n%s wins the game! \n", current.name);
            break;
        }

        if (isFull(board)) {
            displayBoard(board);
            printf("\nIt's a draw!\n");
            break;
        }

        turn++;
    }

    freeBoard(board);
    printf("\nThanks for playing!\n");
    return 0;
}
