/* common.h
 * James Neufeld (neufeld@cs.ualberta.ca)
 *  fuxiang
 */
#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <math.h>
#include <stack>
#include <queue>
#include <list>
#include <ext/hash_map>
#include <ext/hash_set>
#define eps (10e-10)

using namespace std;
using namespace __gnu_cxx;
class state
{

public:

    int x;
    int y;

    double lat;
    double lon;
    pair<double,double> k;
    int num;

    bool operator == (const state &s2) const {
        return ((x == s2.x) && (y == s2.y));
    }

    bool operator != (const state &s2) const {
        return ((x != s2.x) || (y != s2.y));
    }

    bool operator > (const state &s2) const {
        if (k.first-eps > s2.k.first) return true;
        else if (k.first < s2.k.first-eps) return false;
        return k.second > s2.k.second;
    }

    bool operator <= (const state &s2) const {
        if (k.first < s2.k.first) return true;
        else if (k.first > s2.k.first) return false;
        return k.second < s2.k.second + eps;
    }


    bool operator < (const state &s2) const {
        if (k.first + eps < s2.k.first) return true;
        else if (k.first - eps > s2.k.first) return false;
        return k.second < s2.k.second;
    }

};

struct ipoint2 {
    int x,y;
};

struct ivec2 {
    int v[2];
};



struct cellInfo {

    double g;
    double rhs;
    double cost;


};

struct cellInfo2 {

    double f,g,h;
    double cost;
    state * parent;
    void computeF(){
        f = g + f;
    }

};

class state_hash
{
public:
    size_t operator()(const state &s) const {
        return s.x + 34245*s.y;
    }
};


typedef hash_map<state, cellInfo, state_hash, equal_to<state> > ds_ch;
typedef hash_map<state, cellInfo2, state_hash, equal_to<state> > ds_ch2;
typedef hash_map<state, ivec2, state_hash, equal_to<state> > ds_oh;
typedef hash_set<state, state_hash, equal_to<state> > ds_os;
typedef priority_queue<state, vector<state>, greater<state> > ds_pq;

typedef struct {
    list<state> path;
    double cost;

    void clear() {
        path.clear();
        cost = 0.0;
    }

} ds_path;

#endif // COMMON_H_INCLUDED
