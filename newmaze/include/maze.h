#ifndef MAZE_H
#define MAZE_H
#include "basic.h"
#define SPEDR 1
class Maze{
    private:
    int length;
    int width;
    int Blength;
    void areabuild();
    bool cellinitialze(cell*temp,int x_,int y_);
    bool build_();
    bool build_breath();
    cell* next_cell(cell*temp);
    cell*gotry(cell*temp,int i);
    void road_show(cell*temp);
    void road_hide(cell*temp);
    cell*search_next(cell*temp);

public:
    Maze(int len,int wide,int block_len);
    ~Maze();
    void maze_show();
    void build_maze();
    bool roadsearch(int Ox_, int Oy_, int Dx_, int Dy_);
    bool br_search(int Ox_, int Oy_, int Dx_, int Dy_);
};
#endif