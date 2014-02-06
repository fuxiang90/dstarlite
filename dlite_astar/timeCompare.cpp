
#include "Dstar.h"
#ifdef MACOS
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <unistd.h>
#include <stdio.h>
#include "Dstar.h"
#include "Astar.h"
#include "drawutils.h"
#include<sys/time.h>
#include<unistd.h>

int hh, ww;
int scale = 6;
int mbutton = 0;
int mstate = 0;

int sx, sy;
int ex, ey;
bool timeFlag;
Dstar *dstar = new Dstar();
Astar *astar = new Astar();
void updateFunA( )
{
    //选取所有的节点着中一定比例 进行 update
    for(int i = 0 ; i < ex ; i ++){
        for(int j = 0 ; j < ey ; j ++){
            int r = rand()%100;
            if (r == 1 ){
                
                double cost = rand()%100 + 1;
                astar-> updateCell(i,j,cost);

            }
        }
    }
}

void updateFunB( )
{
    //选取所有的节点着中一定比例 进行 update
    for(int i = 0 ; i < ex ; i ++){
        for(int j = 0 ; j < ey ; j ++){
            int r = rand()%100;
            if (r == 1 ){
                double cost = rand()%100 + 1;

                dstar-> updateCell(i,j,cost);
            }
        }
    }
}
double funA(int n)
{

    struct  timeval start;
    struct  timeval end;
    gettimeofday(&start,NULL);
    sx = 0;
    sy = 0;
    astar->init(sx,sy,ex,ey);         // set start to (0,0) and goal to (10,5)
    astar->setRowCol(ex+1,ey+1);
    for(int i = 0 ; i < n ; i ++)
    {

        astar->plan();               // plan a path
        sx ++;
        sy ++;
        astar->updateStart(sx,sy);
        if (timeFlag )
            updateFunA();
    }
    gettimeofday(&end,NULL);

    return  1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
}
double funB(int n)
{


    struct  timeval start;
    struct  timeval end;
    gettimeofday(&start,NULL);
    sx = 0;
    sy = 0;
    dstar->init(sx,sy,ex,ey);         // set start to (0,0) and goal to (10,5)

    for(int i = 0 ; i < n ; i ++)
    {

        dstar->replan();               // plan a path

        sx ++;
        sy ++;
        dstar->updateStart(sx,sy);
        if (timeFlag )
            updateFunB();
    }
    gettimeofday(&end,NULL);

    return  1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
}


int main(int argc, char * argv[])
{
    if (! (argc == 1 || argc == 3 )){
        printf("args num is error");
        return 0;
    }
    int x = atoi(argv[1]);
    if (strcmp(argv[2],"y") == 0){
        timeFlag = true;
    }
    double astarTime = 0.0;
    double dstarTime = 0.0;
    struct  timeval start;
    struct  timeval end;

    sx  = 0;
    sy = 0;
    ex = x;
    ey = x;

    printf("ex: %d ey:%d time :%s\n ",ex,ey,argv[2]);
    for(int i = 0 ; i < 10 ; i ++){
        dstarTime += funB(ex/2);
        astarTime += funA(ey/2);

    }

    printf("astar: %lf,dstar: %lf\n",astarTime, dstarTime);
    printf("运行时间之比:%.2lf\n",astarTime/dstarTime);
    return 0;
}
