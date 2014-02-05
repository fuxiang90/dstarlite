/* Astar.h
 * James Neufeld (neufeld@cs.ualberta.ca)
 * fuxiang90@gmail.com (fuxiang90@gmail.com)
 */

#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <stack>
#include <queue>
#include <list>
#include <ext/hash_map>
#include "common.h"
#define eps (10e-10)

using namespace std;
using namespace __gnu_cxx;



class Astar
{

public:

    Astar();
    void   init(int sX, int sY, int gX, int gY);
    void   updateCell(int x, int y, double val);
    void   updateStart(int x, int y);
    void   updateGoal(int x, int y);
    bool   plan();
    void    setRowCol(int _row, int _col);
//  void   draw() const;
//  void   drawCell(const state &s,float z) const;
//  void   queryCell(int x, int y);

    ds_path &getPath();

private:



    ds_path path;


    state   s_start, s_goal;
    int     row,col;
    int     maxSteps;


    ds_ch2  cellHash;

    ds_pq   openList;
    ds_os   openSet;

    ds_pq   closeList;
    ds_os   closeSet;
    bool    near(double x, double y) const;
    void    makeNewCell(const state &u);
    bool    getBest(state&);
    void    getSucc();
    bool    isGoal(state & s);
    void    expand(const state s );
    double  cost(const state &a, const state &b) const;
    bool    moveIsSave(int x, int y);


};


#endif // ASTAR_H_INCLUDED
