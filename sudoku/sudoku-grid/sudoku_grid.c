#include "sudoku_grid.h"
#include <string.h>

void Sudoku_Grid_init(struct Sudoku_Grid* grid, int* data)
{
    if(data != NULL)
    {
        memcpy(grid->grid, data, sizeof(int) * 81);
    }
    else
    {
    }
}
