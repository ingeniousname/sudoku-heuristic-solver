#include "parser.h"
#include <stdio.h>

struct Sudoku_Grid parse_from_file(const char* filename)
{
    struct Sudoku_Grid res;
    FILE* f = fopen(filename, "r");
    if(f == NULL)
    {
       res.grid[0] = -1;
       return res;
    }

    char buffer[SUDOKU_SIZE + 1];
    fscanf(f, "%s", buffer);

    int buffer_values[SUDOKU_SIZE];
    for(int i = 0; i < SUDOKU_SIZE; i++)
        buffer_values[i] = buffer[i] - '0'; 

    Sudoku_Grid_init(&res, buffer_values);

    fclose(f);
    return res;
}
