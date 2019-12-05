//
// Created by 陈龙飚 on 2019-12-04.
//

#ifndef PLANE_MODEL_H
#define PLANE_MODEL_H
/**
 * 定义飞机
 */
struct Plane{
    int x;
    int y;
    int width;
    int height;
};

/**
 * 定义子弹
 */
struct Bullet{
    int x;
    int y;
    char type; //子弹的符号
    int  flag; //子弹是否出界
};
/**
 * 定义怪
 */
struct Monster{
    int x;
    int y;
    char type; //子弹的符号
    int  flag; //子弹是否出界
};




#endif //PLANE_MODEL_H
