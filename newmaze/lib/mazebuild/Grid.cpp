#include "Grid.h"
static grid*head=NULL,*tail=NULL;

static bool grid_push(grid*temp){
    if(temp==NULL)
    return false;
    temp->NEXT=NULL;
    if(head==NULL){
        head=temp;
        tail=temp;
        temp=NULL;
        return true;
    }
    tail->NEXT=temp;
    tail=temp;
    temp=NULL;
    return true;
}

static bool grid_pop(){
    if(head==NULL){
        return false;
    }
    if(head==tail){
        free(head);
        head=NULL;
        tail=NULL;
        return true;
    }
    grid*temp=head;
    while(temp->NEXT!=tail)
    temp=temp->NEXT;

    free(tail);
    tail=temp;
    temp=NULL;
    tail->NEXT=NULL;
    return true;
}


static grid* search_grid(int x1,int y1,int x2,int y2){
    grid *temp=head;
    while(temp!=NULL){
        if(temp->x1==x1&&temp->x2==x2&&temp->y1==y1&&temp->y2==y2)
        return temp;
        //if(temp->x1==x2&&temp->x2==x1&&temp->y1==y2&&temp->y2==y1)
        //return temp;
        temp=temp->NEXT;
    }
    return NULL;
}

bool Grid:: cls_stack(){
    while(grid_pop()!=false);
    return true;
}

bool Grid::all_show(){
    grid*temp=head;
    while(temp!=NULL){
        temp_grids.push(temp);
        temp=temp->NEXT;
    }
    while(temp_grids.size()!=0){
        Draw_grid(temp_grids.top());
        temp_grids.pop();
    }
    return true;

}


bool Grid::Draw_grid(grid*temp){
    if(temp==NULL)
    return false;
    
    switch(temp->show==none_W){

        case none_W:{
            setlinecolor(WHITE);
            line(temp->x1,temp->y1,temp->x2,temp->y2);
            break;
        }
        default:{
            setlinecolor(BLACK);
            line(temp->x1,temp->y1,temp->x2,temp->y2);
        }
    }
    return true;
}


bool Grid::cell_grid(cell*temp){
    if(temp==NULL)
    return false;
    int _x=grid_len*temp->x1;
    int _y=grid_len*temp->y1;
    if(build_grid(_x, _y, _x, _y + grid_len)==true)
        cell_grid_connect(temp, search_grid(_x, _y, _x, _y + grid_len), L_);
    if(build_grid(_x,_y,_x+grid_len,_y)==true)
        cell_grid_connect(temp, search_grid(_x, _y, _x + grid_len, _y), U_);
    if(build_grid(_x+grid_len, _y, _x+grid_len, _y + grid_len)==true)
        cell_grid_connect(temp, search_grid(_x + grid_len, _y, _x+grid_len, _y + grid_len), R_);
    if (build_grid(_x, _y+grid_len, _x + grid_len, _y+grid_len) == true)
        cell_grid_connect(temp, search_grid(_x, _y + grid_len, _x + grid_len, _y + grid_len), D_);
    return true;
}


bool Grid::cell_grid_connect(cell*cells,grid*grids,dir_T wer){
    if(cells==NULL||grids==NULL)
    return false;
    if(grids->by1==NULL){
      grids->by1=cells;
    }else{
        grids->by2=cells;
    }
    switch(wer){
        case U_:{
            cells->U=grids;
            break;
        }
        case L_:{
            cells->L=grids;
            break;
        }
        case D_:{
            cells->D=grids;
            break;
        }
        case R_:{
            cells->R=grids;
            break;
        }
    }
    return true;
}



bool Grid::build_grid(int x1,int y1,int x2,int y2){
    grid*ser_temp=search_grid(x1,y1,x2,y2);
    if(ser_temp==NULL){
        grid* temp=new_grid();
        if(temp==NULL)
        return false;
        temp->x1=x1;
        temp->x2=x2;
        temp->y1=y1;
        temp->y2=y2;
        temp->show=able_W;
        temp->type=able_W;
        grid_push(temp);
    }else{
        ser_temp->type=stic_W;
    }
    
    Draw_grid(ser_temp);
    return true;
}

grid* Grid::new_grid(){
    grid*temp=(grid*)malloc(sizeof(grid));
    if(temp==NULL)
    return NULL;
    temp->by1=NULL;
    temp->by2=NULL;
    temp->NEXT=NULL;
    temp->show=able_W;
    temp->type=able_W;
    temp->x1=-1;
    temp->y1=-1;
    temp->x2=-1;
    temp->y2=-1;
    return temp;
}



bool Grid :: grid_break(grid*temp){
    if(temp==NULL)
    return false;
    temp->show=none_W;
    Draw_grid(temp);
    return true;
}
bool grid_make(){
return true;
}


void Grid:: setgridlen(int len){
    grid_len=len;
}
int Grid:: getgridlen(){
    return grid_len;
}