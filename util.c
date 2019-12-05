//
// Created by 陈龙飚 on 2019-12-04.
//
#include "util.h"
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>
int _kbhit()
{
    static const int STDIN = 0;
    static int initialized =0;
    if (!initialized)
    {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = 1;
    } int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;

}

char getch(){
    system("stty -echo");
    system("stty -icanon");
    char ch = getchar();
    return ch;
}
