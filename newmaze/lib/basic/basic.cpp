#include "basic.h"
static int char_trans_int(char char_in_) ;
int Type_input(char str[])
{
    int i=0;
    for(;str[i]!='\0';i++){
        if(str[i]>='0'&&str[i]<='9')
        continue;
        return STR;
    }
    if(i==0)
    return STR;
    return NUMBER;
}

int str_trans_int(char *str_in_)
{
    int i = 0, ten = 10, sum = 0;
    for (i = strlen(str_in_) - 1; i >= 0; i--)
    {
        sum += ten * char_trans_int(str_in_[i]) / 10;
        ten *= 10;
    }
    return sum;
}

static int char_trans_int(char char_in_)
{
    return (int)char_in_ - (int)'0';
}