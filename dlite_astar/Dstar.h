/* Dstar.h
 * James Neufeld (neufeld@cs.ualberta.ca)
 */

#ifndef DSTAR_H
#define DSTAR_H

#include <math.h>
#include <stack>
#include <queue>
#include <list>
#include <ext/hash_map>
#include "common.h"
#define eps (10e-10)

using namespace std;
using namespace __gnu_cxx;



class Dstar {

    public:

        Dstar();
        void   init(int sX, int sY, int gX, int gY);
        void   updateCell(int x, int y, double val);
        void   updateStart(int x, int y);
        void   updateGoal(int x, int y);
        bool   replan();
        void   draw() const;
        void   drawCell(const state &s,float z) const;
        void   queryCell(int x, int y);
        void    setRowCol(int _row, int _col);
        int    computeShortestPath();
        ds_path &getPath();

    private:

        ds_path path;

        double C1;
        double k_m;
        state s_start, s_goal, s_last;
        int maxSteps;

        state qstate;

        ds_pq openList;
        ds_ch cellHash;
        ds_oh openHash;

        bool   near(double x, double y) const;
        void   makeNewCell(const state &u);
        double getG(const state &u) const;
        double getRHS(const state &u) const;
        void   setG(const state &u, double g);
        void   setRHS(const state &u, double rhs);
        double eightCondist(const state &a, const state &b) const;
        void   updateVertex(state &u);
        void   insert(state u);
        void   remove(const state &u);
        double trueDist(const state &a, const state &b) const;
        double heuristic(const state &a, const state &b) const;
        state  &calculateKey(state &u) const;
        void   getSucc(state u, list<state> &s) const;
        void   getPred(state u, list<state> &s) const;
        double cost(const state &a, const state &b) const;
        bool   occupied(const state &u) const;
        bool   queuePop();
        bool   isConsistent(const state &u);
};

#endif
