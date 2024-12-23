#ifndef Grid_H
#define Grid_H
#include "basic.h"
class Grid{

    public:
    void setgridlen(int len);
    int getgridlen();
    bool Draw_grid(grid*temp);
    bool cell_grid(cell*temp);
    bool cls_stack();
    bool all_show();
    bool grid_break(grid*temp);
 private : int grid_len;
    stack <grid*> temp_grids;
    grid *new_grid();
    bool build_grid(int x1, int y1, int x2, int y2);
    stack <grid*> grid_temp;
    bool cell_grid_connect(cell*cells,grid*grids,dir_T wer);
};
#endif