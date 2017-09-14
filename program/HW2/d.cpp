#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <queue>
#include <set>
#include <cmath>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()

int n;
int x[1005], y[1005];

struct ufs{
    vector<int> p;

    void init(int n){
        p.resize(n + 1);
        for (int i=0; i<n; i++) p[i] = i;
    }

    int find(int x){
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }

    bool unite(int u, int v){
        u = find(u); v = find(v);
        p[u] = v;
        return u != v;
    }
};


bool judge(double limit){
    ufs u;
    u.init(n);
    for (int i=1; i<=n; i++)
        for (int j=i+1; j<=n; j++)
            if (hypot(double(x[i]-x[j]), double(y[i]-y[j])) <= limit)
                u.unite(i, j);
    return u.find(1) == u.find(2);
}

int main(){
    int T = 0;
    while (scanf("%d", &n), n){
        T++;
        Rep (i, n)
            scanf("%d%d", x+i, y+i);
        double l = 0.0; double r = 2000.0;
        double mid = 0.0;
        while (r - l > 0.0001){
            mid = (r + l) / 2;
            if (judge(mid)) r = mid; else l = mid;
        }
        printf("Scenario #%d\nFrog Distance = %.3f\n\n", T, mid);
    }
    return 0;
}
