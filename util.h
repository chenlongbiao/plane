//
// Created by 陈龙飚 on 2019-12-04.
//

#ifndef PLANE_UTIL_H
#define PLANE_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//获取字符串模拟getch
char getch();
//判断键盘是否输入
int _kbhit();
//打印内容到星号区
void printText(int x,int y,int  ch);
#endif //PLANE_UTIL_H
