#include <stdio.h>
#include <stdbool.h>

#define N 9

// Function prototypes
bool find_empty(int board[N][N], int *row, int *col);
bool is_valid(int board[N][N], int row, int col, int num);
bool solve_sudoku(int board[N][N]);
void print_board(int board[N][N]);

int main() {
    int board[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    printf("Unsolved Sudoku:\n");
    print_board(board);
    printf("\nSolving...\n\n");

    if (solve_sudoku(board)) {
        printf("Solved Sudoku:\n");
        print_board(board);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}

// Function to find an empty cell in the board
bool find_empty(int board[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (board[*row][*col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Function to check if placing num in board[row][col] is valid
bool is_valid(int board[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num) {
            return false;
        }
}
    for (int i = 0; i < N; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }
    int start_row = row - (row % 3);
    int start_col = col - (col % 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[start_row + i][start_col + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// Main function to solve Sudoku using backtracking
bool solve_sudoku(int board[N][N]) {
    int row, col;

    // If there is no empty cell, Sudoku is solved
    if (!find_empty(board, &row, &col)) {
        return true;
    }

    // Try numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (is_valid(board, row, col, num)) {
            board[row][col] = num;

            // Recursively solve rest of the puzzle
            if (solve_sudoku(board)) {
                return true;
            }

            // Backtrack if no solution found with current num
            board[row][col] = 0;
        }
    }

    return false; // No solution exists
}

// Function to print the Sudoku board
void print_board(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}
