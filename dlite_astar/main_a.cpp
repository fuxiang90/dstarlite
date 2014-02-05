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
#include "Astar.h"
#include "drawutils.h"

int hh, ww;
int scale = 6;
int mbutton = 0;
int mstate = 0;


bool b_autoreplan = true, b_examine_mode=false;

void show(ds_path &  _path)
{
    printf("===========================\n");
    list<state> path = _path.path;
    for(list<state>::iterator iter = path.begin() ; iter != path.end() ; iter++ ) {
        printf("%d %d \n",iter->x, iter->y);
    }
}

//void InitGL(int Width, int Height)
//{
//  hh = Height;
//  ww = Width;
//
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//    glClearDepth(1.0);
//
//    glViewport(0,0,Width,Height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0,Width,0,Height,-100,100);
//    glMatrixMode(GL_MODELVIEW);
//
//}
//void DrawGLScene()
//{
//
//  char str[256];
//
//  usleep(100);
//
//  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//  glLoadIdentity();
//  glPushMatrix();
//
//  glScaled(scale,scale,1);
//
//  if (b_autoreplan) dstar->replan();
//  if (b_examine_mode) sprintf(str,"Examine Mode");
//  else sprintf(str,"Cost draw mode: %f",cost);
//
//  DisplayStr(str,GLUT_BITMAP_HELVETICA_18,1,1,1,0.01,0.92);
//
//  dstar->draw();
//
//  glPopMatrix();
//  glutSwapBuffers();
//
//}
//void ReSizeGLScene(int Width, int Height)
//{
//  hh = Height;
//  ww = Width;
//
//  glViewport(0,0,Width,Height);
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  glOrtho(0,Width,0,Height,-100,100);
//  glMatrixMode(GL_MODELVIEW);
//
//}


int main(int argc, char **argv)
{

//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
//    glutInitWindowSize(1000, 800);
//    glutInitWindowPosition(50, 20);
//
//    window = glutCreateWindow("Dstar Visualizer");
//
//    glutDisplayFunc(&DrawGLScene);
//    glutIdleFunc(&DrawGLScene);
//    glutReshapeFunc(&ReSizeGLScene);
//
//
//    InitGL(800, 600);
    Astar *astar = new Astar();

    astar->init(0,0,2,2);         // set start to (0,0) and goal to (10,5)

    astar->plan();               // plan a path

    return 0;
}

