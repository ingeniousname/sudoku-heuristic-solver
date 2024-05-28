#include "utils.h"
#include <stdio.h>

void print_sudoku(struct Sudoku_Grid* grid)
{
    printf("\n");
    for(int row = 0; row < SUDOKU_N; row++)
    {
        if (row % 3 == 0)
            printf("-------------------------------\n");
        for (int col = 0; col < SUDOKU_N; col++)
        {
            if (col % 3 == 0)
                printf("|");
            printf(" %d ", grid->grid[row * SUDOKU_N + col]);
        }
        printf("|\n");
        if (row == SUDOKU_N - 1)
            printf("-------------------------------\n");
    }
    printf("\n");
}

int validate_solution(struct Sudoku_Grid* grid)
{
    // check rows
    for (int i = 0; i < SUDOKU_N; ++i)
    {
        int validator = 0;
        for (int j = 0; j < SUDOKU_N; ++j)
        {
            int value = grid->grid[i * SUDOKU_N + j];
            int is_valid = (1 << value) & (validator);
            if (is_valid != 0)
                return 0;
            validator |= (1 << value);
        }
    }

    // check columns
    for (int i = 0; i < SUDOKU_N; ++i)
    {
        int validator = 0;
        for (int j = 0; j < SUDOKU_N; ++j)
        {
            int value = grid->grid[i + SUDOKU_N * j];
            int is_valid = (1 << value) & (validator);
            if (is_valid != 0)
                return 0;
            validator |= (1 << value);
        }
    }

    //check subboards
    for (int i = 0; i < SUDOKU_N; ++i)
    {
        int validator = 0;
        int start = ((i / 3) * 3) * SUDOKU_N + ((i % 3) * 3);
        for (int j = 0; j < SUDOKU_N; ++j)
        {
            int r = j / 3;
            int c = j % 3;
            int value = grid->grid[start + r * SUDOKU_N + c];
            int is_valid = (1 << value) & (validator);
            if (is_valid != 0)
                return 0;
            validator |= (1 << value);

        }
    }

    return 1;
}
