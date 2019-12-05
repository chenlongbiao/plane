#include "ansi.h"
#include "util.h"
#include "model.h"




/**
 * 定义盒子的宽高
 */
int width = 70;
int height = 22;

/**
 * 定义星号区的起始位置
 */

int starStart = 72;
int starEnd = 92;
/**
 * 定义左右边界的字符
 */
char flag = '-';
char flag2 = '|';

char flag3 = '*';

int score = 0;



/**
 * 声明画盒子的方法
 */
void  drawBox();
/**
 * 声明画飞机的方法
 */
void  drawPlane(struct Plane plane);
/**
 * 声明擦除飞机的方法
 */
void  clearPlane(struct Plane plane);
/**
 * 声明向左移动的方法
 */
void  goLeft(struct Plane *plane);
/**
 * 声明向右移动的方法
 */
void  goRight(struct Plane *plane);
/**
 * 声明向上移动的方法
 */
void goUp(struct Plane *plane);
/**
 * 声明向下移动的方法
 */
void  goDown(struct Plane *plane);

/**
 * 声明移动飞机的方法
 */
void controlPlane(struct Plane *plane);

/**
 * 声明子弹到界面外初始化的方法
 */
void initAllBullet(struct Bullet arr[],int num);


/**
 * 声明画子弹的方法
 */
 void drawBullet(struct Bullet arr[],int num);
/**
 * 声明更新子弹位置的方法
 */
void updateBullet(struct Bullet arr[],int num);
/**
 * 声明产生子弹的方法
 */
void newBullet(struct Bullet arr[],int num, struct Plane plane);

/**
 * 声明怪物到界面外初始化的方法
 */
void initAllMonster(struct Monster arr[],int num);


/**
 * 声明画怪物的方法
 */
void drawMonster(struct Monster arr[],int num);

/**
 * 声明更新子弹位置的方法
 */
void updateMonster(struct Monster arr[],int num);
/**
 * 声明产生子弹的方法
 */
void newMonster(struct Monster arr[],int num);

/**
 * 声明检测子弹与怪物碰撞的方法
 */
void checkCollision(struct Bullet arr[],int num,struct Monster arr1[], int num1);

/**
 * 声明检测飞机与怪物碰撞的方法
 */
void checkGameOver(struct Plane plane,struct Monster arr[], int num);

int main() {
//    //画盒子
    drawBox();
    //画飞机
    struct Plane plane = {width/2-1, height-3,3,2};
    drawPlane(plane);


    //初始化子弹
    struct Bullet bulletArray[25];
    initAllBullet(bulletArray,25);

    //初始化怪物
    struct Monster monsterArray[70];
    initAllMonster(monsterArray,70);



    int count = 0;
    while (1){
        controlPlane(&plane);

        //循环3次生成一个子弹
        if (count %3 == 0){
            newBullet(bulletArray,25,plane);
        }
        //循环6次生成一个怪物
        if(count%6 == 0){
            newMonster(monsterArray,25);
        }
        drawBullet(bulletArray,25);
        drawMonster(monsterArray,25);

        usleep(50000);

        updateBullet(bulletArray,25);
        updateMonster(monsterArray,70);


        checkCollision(bulletArray,25,monsterArray,70);
//
        checkGameOver(plane,monsterArray,25);

        count++;
    }
}


/**
 * 画盒子
 */
void drawBox(){
    CLEAR();
    for (int i=0;i<width;i++){
        MOVETO(i,0);
        printf("%c",flag);
    }
    printf("\n");

    for (int i=0;i<width;i++){
        MOVETO(i,height-1);
        printf("%c",flag);
    }
    printf("\n");
    for (int j = 0; j < height ; ++j) {
        MOVETO(1,j);
        printf("%c",flag2);
    }

    for (int j = 0; j < height ; ++j) {
        MOVETO(width-1,j);
        printf("%c",flag2);
    }

    /**
     * 画右面星号区
     */
    for (int i=starStart;i<starEnd;i++){
        MOVETO(i+2,0);
        printf("%c",flag3);
    }
    printf("\n");

    for (int i=starStart;i<starEnd;i++){
        MOVETO(i+2,height-1);
        printf("%c",flag3);
    }
    printf("\n");
    for (int j = 0; j < height  ; ++j) {
        MOVETO(starStart+1,j);
        printf("%c",flag3);
    }

    for (int j = 0; j < height ; ++j) {
        MOVETO(starEnd+1,j);
        printf("%c",flag3);
    }

    MOVETO(starStart+3,3);
    printf("%s","当前输入的字符:");
    MOVETO(starStart+3,4);
    printf("%s:%d","当前得分",score);


}
/**
 * 画飞机
 */
void  drawPlane(struct Plane plane){
    MOVETO(plane.x,plane.y);
    printf("|\n");
    MOVETO(plane.x-1,plane.y+1);
    printf("/|\\\n");
}
/**
 * 清除飞机
 */
void clearPlane(struct Plane plane){
    MOVETO(plane.x,plane.y);
    printf("   \n"); //三个空格
    MOVETO(plane.x-1,plane.y+1);
    printf("   \n"); //三个空格
}
/**
 * 向左移动的方法
 */
void  goLeft(struct Plane *plane){
    if (plane->x<5)
        return;
    plane->x--;
}
/**
 * 向右移动的方法
 */
void  goRight(struct Plane *plane){
    if (plane->x+plane->width>width-2)
        return;
    plane->x++;
}
/**
 * 向上移动的方法
 */
void goUp(struct Plane *plane){
    if (plane->y<3)
        return;
    plane->y--;
}
/**
 * 向下移动的方法
 */
void  goDown(struct Plane *plane){
    if (plane->y+plane->height>height-2)
        return;
    plane->y++;
}
/**
 * 根据输入结果。控制飞机
 */
int i = 0;
void controlPlane(struct Plane *plane){
    i = _kbhit();
    if (i>0){
            char ch = getch();
            clearPlane(*plane);
            switch (ch){
                case 'a' :
                    goLeft(plane);
                    MOVETO(starStart+19,3);
                    printf("%c",ch);
                    break;
                case 'w':
                    goUp(plane);
                    MOVETO(starStart+19,3);
                    printf("%c",ch);
                    break;
                case 's':
                    goDown(plane);
                    MOVETO(starStart+19,3);
                    printf("%c",ch);
                    break;
                case 'd':
                    goRight(plane);
                    MOVETO(starStart+19,3);
                    printf("%c",ch);
                    break;
                default:
                    break;
            }
            drawPlane(*plane);

    }

}

/**
 * 初始化子弹到界面外
 */
void initAllBullet(struct Bullet arr[],int num){
    for(int i = 0;i<num;i++){
        arr[i].flag = 1;
    }
}


/**
 * 画子弹的方法 按照子弹的位置。将所有的子弹画出来
 */
void drawBullet(struct Bullet arr[],int num){
    for (int i = 0; i < num; ++i) {
        if (arr[i].flag == 1){ //界面外的子弹交给生成子弹去处理。这里直接忽略
            continue;
        }
        MOVETO(arr[i].x,arr[i].y);
        printf("%c\n",arr[i].type);
    }
}

/**
 * 更新子弹位置的方法
 */
void updateBullet(struct Bullet arr[],int num){
    for (int i = 0; i < num; ++i) {
        if (arr[i].flag == 1){
            continue;
        }
        MOVETO(arr[i].x,arr[i].y);
        printf(" "); //清除子弹
        arr[i].y--;  //将子弹的位置往上移动一个位置

        if (arr[i].y < 2){  //是否出界面 出界面把标记为1
            arr[i].flag = 1;
        }
    }
}

/**
 * 产生子弹的方法
 */
void newBullet(struct Bullet arr[],int num, struct Plane plane){
    for (int i = 0; i < num; ++i) {
        if (arr[i].flag == 1){ //将界面外的子弹位置调整回来
            arr[i].x = plane.x+1; //子弹在飞机正中央
            arr[i].y = plane.y -1; //子弹在飞机上面
            arr[i].type = '*';
            arr[i].flag = 0;
            return;
        }
    }
}


/**
 * 怪物到界面外初始化的方法
 */
void initAllMonster(struct Monster arr[],int num){
    for(int i = 0;i<num;i++){
        arr[i].flag = 1;
    }
}


/**
 * 画怪物的方法
 */
void drawMonster(struct Monster arr[],int num){
    for (int i = 0; i < num; ++i) {
        if (arr[i].flag == 1){ //界面外的子弹交给生成子弹去处理。这里直接忽略
            continue;
        }
        MOVETO(arr[i].x,arr[i].y);
        printf("%c\n",arr[i].type);
    }
}

/**
 * 更新怪物位置的方法
 */
void updateMonster(struct Monster arr[],int num){
    for (int i = 0; i < num; ++i) {
        if (arr[i].flag == 1){
            continue;
        }
        MOVETO(arr[i].x,arr[i].y);
        printf(" "); //清除怪物
        arr[i].y++;  //将怪物的位置往下移动一个位置

        if (arr[i].y > height-2){  //是否出界面 出界面把标记为1
            arr[i].flag = 1;
        }
    }
}

/**
 * 产生怪物的方法
 */
void newMonster(struct Monster arr[],int num){
    for (int i = 0; i < num; ++i) {
        if (arr[i].flag == 1){ //将界面外的怪物位置调整回来
            arr[i].x = rand()%(width-4)+2; //怪物随机产生
            arr[i].y = 1; //怪物在屏幕最上面上面
            arr[i].type = '@';
            arr[i].flag = 0;
            return;
        }
    }
}

/**
 * 子弹与怪物碰撞的方法
 * @param arr 子弹列表
 * @param num 子弹数量
 * @param arr1 怪物列表
 * @param num1 怪物数量
 */

void checkCollision(struct Bullet arr[],int num,struct Monster arr1[], int num1){
    for (int i = 0; i < num; ++i) {
        if (arr[i].flag == 1){
            continue;
        }

        for (int j = 0; j < num1; ++j) {
            if (arr1[j].flag == 1){
                continue;
            }
            //检查是否碰撞了 判断坐标是否相等   同时判断是否有当前时刻x相等但是 y已经碰撞过了的。 即 子弹的y坐标比怪物的y坐标小的
            if((arr[i].x == arr1[j].x && arr[i].y == arr1[j].y) || (arr[i].x == arr1[j].x && arr[i].y<arr1[j].y)){
                arr[i].flag = 1; //将子弹移除界面
                arr1[j].flag = 1; //将怪物移除界面
                score++;
                printText(starStart+19,6,score);
            }
        }
    }
}


/**
 * 检测飞机与怪物碰撞的方法
 */
void checkGameOver(struct Plane plane,struct Monster arr[], int num){
    for (int i = 0; i < num; ++i) {
        if (arr[i].flag == 1){
            continue;
        }
        //检查是否碰撞了 判断坐标是否相等   同时判断是否有当前时刻x相等但是 y已经碰撞过了的。 即 子弹的y坐标比怪物的y坐标小的
        if((arr[i].x >= plane.x && arr[i].x <plane.x+plane.width)
        &&( arr[i].y >= plane.y && arr[i].y< plane.y+plane.height)){
            system("clear");
            printf("Game Over");
            exit(0);
        }
    }
}


void printText(int x,int y,char ch[]){
    if (x == 0)
        x = starStart+19;
    if (y == 0)
        y = 3;
    MOVETO(x,y);
    printf("%s",ch);
}