#ifndef BASIC_M
#define BASIC_M 0
#define NUMBER 11
#define STR 22
#include <string.h>
#include"easyx.h"
#include"graphics.h"
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
int Type_input(char str[]);
int str_trans_int(char *str_in_);
#endif

#ifndef STRUCT_H
#define STRUCT_H
enum wall
{
    stic_W,
    none_W,
    able_W,
    block_W
};

enum dir_T{
    U_,
    L_,
    D_,
    R_,
    NOWER
};

typedef struct cell_msg cell;

typedef struct Grid_msg
{
    int x1, y1, x2, y2;
    wall type;
    wall show;
    cell*by1;
    cell*by2;

    struct Grid_msg*NEXT;
} grid;

typedef struct cell_msg
{
    int x1,y1;
    grid*U;
    grid*L;
    grid*D;
    grid*R;


    struct cell_msg*NEXT;
}cell;


typedef struct tree_breath_road
{
    struct tree_breath_road* front_;
    cell*cell_now;

}Ptree;


#endif