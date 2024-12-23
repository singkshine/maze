#include <iostream>
#include"graphics.h"
#include"easyx.h"
#include "maze.h"
#include "Grid.h"
#include "windows.h"
using namespace std;
int main(int argc, char** argv) {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	int len,wid,blen;
	cout<<"输入长度"<<endl;
	cin>>len;
	cout<<"输入宽度"<<endl;
	cin>>wid;
	cout<<"输入方块边长"<<endl;
	cin>>blen;
	Maze new_maze(len,wid,blen);
	new_maze.maze_show();
	new_maze.build_maze();
	new_maze.maze_show();
	int x1,y1,x2,y2;
	cout<<"x1:";
	cin>>x1;
	cout<<"y1:";
	cin>>y1;
	cout<<"x2:";
	cin>>x2;
	cout<<"y2:";
	cin>>y2;
	new_maze.br_search(x1,y1,x2,y2);
	cin>>x1;
	Grid clss;
	clss.cls_stack();
	//画线条
	//initgraph(len,wid,blen);





return 0;
}