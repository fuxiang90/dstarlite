#include "Astar.h"

Astar::Astar() {

    maxSteps = 80000;

}
void    Astar::init(int sX, int sY, int gX, int gY)
{
    s_start.x = sX;
    s_start.y = sY;

    s_goal.x = gX;
    s_goal.y = gY;

    makeNewCell(s_start);
    makeNewCell(s_goal);

    row = 20;
    col = 20;
}
bool    Astar::moveIsSave(int x, int y)
{
    if (x < row && x >=0 &&  y < col  && y >=0 )
        return true;
    else
        return false;
}
void   Astar::updateCell(int x, int y, double val)
{
    state u ;
    u.x = x;
    u.y = y;
    if (u == s_start || u == s_goal) return ;

    //ds_ch::iterator cur = cellHash.find(u);
    //if (cur != cellHash.end() ) return;

    makeNewCell(u);
    cellHash[u].cost = val;
}
    void   updateStart(int x, int y);
    void   updateGoal(int x, int y);

void    Astar::makeNewCell(const state &u)
{

    if (cellHash.find(u) != cellHash.end()) return;

    cellInfo2 tmp;
    tmp.f       = tmp.g =   tmp.h = INFINITY; //heuristic(u,s_goal);
    tmp.cost    = 1.0;
    cellHash[u] = tmp;

}
bool Astar::isGoal(state & s)
{
    return s == s_goal;
}
bool Astar::getBest(state & result)
{
    if (openSet.empty() == true) {
        return false;
    }
    state s ;

    /*
        do{
            s = openList.top();
            openlist.pop();
        }while(openHash.find(s) != openHash.end() &&  openList.empty() == false)

        if (openHash.find(s) != openHash.end() ){
            result = s;
            return true;
        }else{
            return false;
        }
    */
    ds_os::iterator iter = openSet.begin();
    s = *iter ;
    iter ++;
    for( ;iter != openSet.end() ; iter ++ ) {
        if (cellHash[*iter].f <cellHash[s].f) {
            s = *iter;
        }
    }
    result = s;
    return true;

}
void    Astar::expand(const state s )
{
    const static int dx[8]= {1, 1, 0, -1, -1, -1, 0, 1};
    const static int dy[8]= {0, 1, 1, 1, 0, -1, -1, -1};
    for(int i = 0 ; i < 8 ; i ++) {
        state next ;
        next.x = s.x + dx[i];
        next.y = s.y + dy[i];
        if (moveIsSave(next.x, next.y) == false ) {
            return ;
        }

        makeNewCell(next);

        double _f,_g,_h;

        _g = cellHash[s].g + cost(next,s) + cellHash[next].cost;
        _h = cost(next,s_goal);
        _f = _g + _h;



        if(closeSet.find(next) == closeSet.end() ) { //not in closeSet
            if(openSet.find(next) == openSet.end() ) {

                cellHash[next].g = _g;
                cellHash[next].h = _h;
                cellHash[next].f = _f;
                openSet.insert(next);
            } else {
                if(cellHash[next].f > _f) {
                    cellHash[next].g = _g;
                    cellHash[next].h = _h;
                    cellHash[next].f = _f;
                }
            }
        } else {

            if(cellHash[next].f > _f) {
                cellHash[next].g = _g;
                cellHash[next].h = _h;
                cellHash[next].f = _f;

                closeSet.erase(next);
                openSet.insert(next);
            }
        }

    }
}
bool   Astar::plan()
{
    //s_start.k = 0.0;
    cellHash[s_start].f = cellHash[s_start].cost + cost(s_start,s_goal);
    cellHash[s_start].g = cellHash[s_start].cost  ;
    cellHash[s_start].h = cost(s_start,s_goal);
    openSet.insert(s_start);
    //openList.push(s_start);

    state best;
    bool flag = false;
    int _step = 0;
    while(openList.empty() == true ) {

        if (false == getBest(best) ) {
            break;
        }

        if(isGoal(best) == true) {

            flag = true;
#ifdef DEBUG
            printf("get the goal \n");
#endif
            break;
        }

        expand(best);

        openSet.erase(best);
        closeSet.insert(best);
        _step ++ ;

#ifdef DEBUG
        printf("openset size %d  , %d\n",openSet.size(),_step);
#endif
    }

    return flag;

}
double Astar::cost(const state &a, const state &b) const
{

    int xd = abs(a.x-b.x);
    int yd = abs(a.y-b.y);
    return sqrt((xd^2) +(yd^2));
}
