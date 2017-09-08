#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cfloat>
#include <numeric>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
#define pb push_back
#define mt make_tuple
#define read(n) scanf("%d", &(n))
typedef long long LL;

double k;
struct pt{
    int x, y, z;
};
const int MAXN = 1024;
int n;
pt pts[MAXN];

int cost[MAXN][MAXN];
double dist[MAXN][MAXN];
double adj[MAXN][MAXN];

int prev[MAXN];
bool done[MAXN];
double key[MAXN];
double prim2(){
    Rep (i, n){
        Rep (j, n){
            adj[i][j] = cost[i][j] - k * dist[i][j];
        }
    }
    Rep (i, n){
        done[i] = false;
        key[i] = DBL_MAX;
    }
    key[1] = 0.0; prev[1] = 0;
    rep (cnt, n){
        int u;
        double k = DBL_MAX;
        Rep (i, n){
            if (!done[i] && key[i] < k){
                u = i; k = key[i];
            }
        }
        done[u] = true;
        Rep (v, n){
            if (!done[v] && adj[u][v] < key[v]){
                key[v] = adj[u][v];
                prev[v] = u;
            }
        }
    }
    double totcost = 0.0, totlen = 0.0;
    for (int i=2; i<=n; i++){
        totcost += cost[prev[i]][i];
        totlen += dist[prev[i]][i];
    }
    return totcost / totlen;
}


int main(){
    ios::sync_with_stdio(false);    cin.tie(0);
    while (read(n), n){
        Rep (i, n)
            read(pts[i].x), read(pts[i].y), read(pts[i].z);
        Rep (i, n)
            Rep (j, n)
                dist[i][j] = hypot(double(pts[i].x - pts[j].x), double(pts[i].y - pts[j].y)),
                cost[i][j] = abs(pts[i].z - pts[j].z);
        k = 1e5;
        double nxt;
        while (fabs((nxt = prim2()) - k) > 1e-6){
            k = nxt;
        }
        printf("%.3f\n", nxt);
    }
    return 0;
}
