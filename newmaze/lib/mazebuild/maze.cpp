#include "maze.h"
#include "basic.h"
#include "Grid.h"
#include "time.h"
#include "stdlib.h"
#include "windows.h"
#include "graphics.h"
#include "easyx.h"
#include <queue>
#ifndef MAZE_C
#define MAZE_C
static cell*head=NULL,*tail=NULL;
static bool cell_push(cell *temp);
static bool cell_pop();
static cell *cell_top();
#endif
Maze::Maze(int len, int wide, int block_len) : length(len), width(wide), Blength(block_len) {};



Maze::~Maze(){
    while(cell_pop()!=false);
}

static bool cell_push(cell*temp){
    if(temp==NULL)
    return false;
    temp->NEXT=NULL;
    if(head==NULL){
        head=temp;
        tail=temp;
    }else{
        tail->NEXT=temp;
        tail=temp;
    }
    temp=NULL;
    return true;
}
static bool cell_pop(){
    if(head==NULL)
    return false;
    if(head==tail){
        free(head);
        head=NULL;
        tail=NULL;
    }else{
        cell*temp=head;
        while(temp->NEXT!=tail){
            temp=temp->NEXT;
        }
        free(tail);
        tail=temp;
        tail->NEXT=NULL;
        temp=NULL;
    }
    return true;
}

static cell*cell_top(){
    return tail;
}



static cell*search_cell(int x_,int y_){
    if(head==NULL)
    return NULL;
    cell*temp=head;
    while(temp!=NULL){
        if(temp->x1==x_&&temp->y1==y_)
        return temp;
        temp=temp->NEXT;
    }
    return NULL;
}

void Maze::maze_show()
{
    int leng = (length+2) * Blength;
    int wideth = (width+2) * Blength;
    initgraph(leng,wideth);
    setcolor(WHITE);
    fillrectangle(0,0,leng,wideth);
    Grid temper;
    temper.setgridlen(Blength);
    temper.all_show();
    
}

void Maze:: build_maze(){
    Grid Grids_;
    Grids_.cls_stack();
    Grids_.setgridlen(Blength);
    areabuild();
    //areabuild();
    build_();
   // build_breath();
}











void Maze:: areabuild(){
    int i=0,j=0;
    Grid tempers;
    tempers.setgridlen(Blength);
    for(i=0;i<=length+1;i++){
        if(search_cell(i,0)==NULL){
        cell*boundray=(cell*)malloc(sizeof(cell));
        cellinitialze(boundray,i,0);
        tempers.cell_grid(boundray);
        cell_push(boundray);
        }
    }

    for(i=0;i<=length+1;i++){
        if (search_cell(i,width+1) == NULL)
        {
            cell *boundray = (cell *)malloc(sizeof(cell));
            cellinitialze(boundray, i, width+1);
            tempers.cell_grid(boundray);
            cell_push(boundray);
        }
    }
    for (i = 0; i <=width+1; i++)
    {
        if (search_cell(0,i) == NULL)
        {
            cell *boundray = (cell *)malloc(sizeof(cell));
            cellinitialze(boundray, 0,i);
            tempers.cell_grid(boundray);
            cell_push(boundray);
        }
    }
    for (i = 0; i <= width + 1; i++)
    {
        if (search_cell(length+1, i) == NULL)
        {
            cell *boundray = (cell *)malloc(sizeof(cell));
            cellinitialze(boundray, length+1, i);
            tempers.cell_grid(boundray);
            cell_push(boundray);
        }
    }
}

bool Maze::cellinitialze(cell*temp,int x_,int y_){
    if(temp==NULL)
    return false;
    
    temp->D=NULL;
    temp->L=NULL;
    temp->R=NULL;
    temp->U=NULL;
    temp->NEXT=NULL;
    temp->x1=x_;
    temp->y1=y_;

    return true;

}

bool Maze::build_(){
    stack <cell*> stepcol;



    srand(time(NULL));


    cell*start_=(cell*)malloc(sizeof(cell));


    cellinitialze(start_,rand()%length+1,rand()%width+1);
    Grid setwall;
    setwall.setgridlen(Blength);
    setwall.cell_grid(start_);
    stepcol.push(start_);
    cell_push(start_);
    //setwall.all_show();



    int step=1;



    while(step<length*width){
        cell*temp=next_cell(stepcol.top());
        if(temp==NULL){//no cell
            stepcol.pop();
        continue;
        }else{
        stepcol.push(temp);
        cell_push(temp);
        step++;
        //setwall.all_show();
        }

    }
    return true;


}

bool Maze::build_breath(){
    srand(time(NULL));
    queue <cell*> stepcol;

    cell*start_=(cell*)malloc(sizeof(cell));

    cellinitialze(start_,rand()%length+1,rand()%width+1);
    Grid setwall;
    setwall.setgridlen(Blength);
    setwall.cell_grid(start_);
    stepcol.push(start_);
    cell_push(start_);
    int i=1;
    cell *temp = next_cell(stepcol.front());
     while (stepcol.empty() != true){
        int k=0;
        while(temp!=NULL){
        cell*temp=next_cell(stepcol.front());
        if(temp==NULL||k>0)
        break;
       // i++;
        k++;
        stepcol.push(temp);
        cell_push(temp);
        }
        stepcol.pop();
      // i--;
      // while(i>40){
     //   i--;
     //   stepcol.pop();
       //}
    }
        maze_show();
    return true;



}


cell* Maze::next_cell(cell* temp){
    cell* next_pls=NULL;
    int turn[5];
    int k=0,i=0;
    for(k=0;k<5;k++)
    turn[k]=0;
    k=0;
    while(1==1){
    i=rand()%4+1;
        if(i==turn[0]||i==turn[1]||i==turn[2]){
            continue;
        }
        next_pls = gotry(temp, i);//////


        if(next_pls!=NULL)
            return next_pls;
        turn[k]=i;
        k++;
        if(k>=4){
            return NULL;
        }
    }
}

cell* Maze::gotry(cell*temp,int i){
    int j=0;
    int x_=temp->x1,y_=temp->y1;
    grid *mid_=NULL;
    switch(i){
        case 1:{
            if(temp->U->type==stic_W)
            return NULL;
            y_=temp->y1-1;
            mid_=temp->U;
            break;
        }
        case 2:{
            if(temp->L->type==stic_W)
            return NULL;
            x_=temp->x1-1;
            mid_=temp->L;
            break;
        }
        case 3:{
            if(temp->D->type==stic_W)
            return NULL;
            y_=temp->y1+1;
            mid_=temp->D;
            break;
        }
        case 4:{
            if(temp->R->type==stic_W)
            return NULL;
            x_=temp->x1+1;
            mid_=temp->R;
            break;
        }
    }

    //cout<<endl<<"b"<<x_<<','<<y_<<endl;
    

    Grid temper_grid;
    temper_grid.setgridlen(Blength);
    cell*next_pls=(cell*)malloc(sizeof(cell));
    cellinitialze(next_pls,x_,y_);
    temper_grid.cell_grid(next_pls);
    temper_grid.grid_break(mid_);
    return next_pls;

}

bool Maze::roadsearch(int Ox_,int Oy_,int Dx_,int Dy_){
    cell *O_P=search_cell(Ox_,Oy_);
    if(O_P==NULL)
    return false;
    road_show(O_P);
    cell *D_P=search_cell(Dx_,Dy_);
    if(D_P==NULL)
    return false;
    road_show(D_P);
    stack <cell*> passroad;
    passroad.push(O_P);
    while(passroad.top()!=D_P){
        O_P=search_next(passroad.top());
        if(O_P==NULL){
            road_hide(passroad.top());
            passroad.pop();
            continue;
            }
            passroad.push(O_P);
            road_show(passroad.top());
    }


    return true;////ing
}

















cell* Maze::search_next(cell*temp){
    if(temp->U->show==none_W&&temp->U->type!=block_W){
        temp->U->type=block_W;
        if(temp->U->by1==temp)
        return temp->U->by2;
        return temp->U->by1;
    }
    if (temp->D->show == none_W && temp->D->type != block_W)
    {
        temp->D->type = block_W;
        if (temp->D->by1 == temp)
            return temp->D->by2;
        return temp->D->by1;
    }
    if (temp->L->show == none_W && temp->L->type != block_W)
    {
        temp->L->type = block_W;
        if (temp->L->by1 == temp)
            return temp->L->by2;
        return temp->L->by1;
    }
    if (temp->R->show == none_W && temp->R->type != block_W)
    {
        temp->R->type = block_W;
        if (temp->R->by1 == temp)
            return temp->R->by2;
        return temp->R->by1;
    }

    return NULL;
}





void Maze::road_show(cell*temp){
    if(temp==NULL)
    return ;
    Sleep(SPEDR);
    int x1_=temp->x1*Blength;
    int y1_=temp->y1*Blength;
    int x2_=(1+temp->x1)*Blength;
    int y2_=(1+temp->y1)*Blength;
    setcolor(BLACK);
    line(x1_,y1_,x2_,y2_);
    line(x2_,y1_,x1_,y2_);
    return;
}

void Maze::road_hide(cell *temp)
{
    if (temp == NULL)
        return;
        Sleep(SPEDR);
    int x1 = temp->x1 * Blength;
    int y1 = temp->y1 * Blength;
    int x2 = (temp->x1 + 1) * Blength;
    int y2 = (temp->y1 + 1) * Blength;
    setcolor(WHITE);
    line(x1, y1, x2, y2);
    line(x2, y1, x1, y2);
    return;
}

bool Maze::br_search(int Ox_, int Oy_, int Dx_, int Dy_)
{
    queue <Ptree*>tree_P;
    queue <Ptree*>all_P;
    cell *O_P = search_cell(Ox_, Oy_);
    if (O_P == NULL)
        return false;
    road_show(O_P);
    cell *D_P = search_cell(Dx_, Dy_);
    if (D_P == NULL)
        return false;
    Ptree *roots=(Ptree*)malloc(sizeof(Ptree));
    roots->cell_now=O_P;
    roots->front_=NULL;
    tree_P.push(roots);
    all_P.push(roots);
    while(tree_P.front()->cell_now!=D_P){
        cell* Next_ =search_next(tree_P.front()->cell_now);
        if(Next_!=NULL){
            Ptree *branch=(Ptree*)malloc(sizeof(Ptree));
            branch->cell_now=Next_;
            branch->front_=tree_P.front();
            tree_P.push(branch);
            all_P.push(branch);
            road_show(Next_);
            if(Next_==D_P){
            roots=branch;
            break;
            }
        }else{
            tree_P.pop();
        }

    }
    queue <Ptree*>temp_;
    while(all_P.empty()!=true){
        temp_.push(all_P.front());
        road_hide(all_P.front()->cell_now);
        all_P.pop();
    }
    //roots=tree_P.front();
    while(roots->front_!=NULL){
        road_show(roots->cell_now);
        roots=roots->front_;
    }
    while(temp_.empty()!=true){
        free(temp_.front());
        temp_.pop();
    }
    return true;

}



