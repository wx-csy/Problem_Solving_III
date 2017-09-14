#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <queue>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()

struct edge{
    int u, v, w;
} edges[20005];

int n, m = 0;
int d[205];

const int INF = INT_MAX - 1000006;
int main(){
    int ml, md;
    scanf("%d%d%d", &n, &ml, &md);
    while (ml--){
        scanf("%d%d%d", &edges[m].u, &edges[m].v, &edges[m].w);
        m++;
    }
    while (md--){
        scanf("%d%d%d", &edges[m].v, &edges[m].u, &edges[m].w);
        edges[m].w = -edges[m].w;
        m++;
    }
    for (int i=2; i<=n; i++){
        d[i] = INF;
    }
    d[1] = 0;
    int i;
    bool flag;
    for (i = 0; i < n; i++){
        flag = false;
        for (int j = 0; j < m; j++){
            if (d[edges[j].v] > d[edges[j].u] + edges[j].w){
                d[edges[j].v] = d[edges[j].u] + edges[j].w;
                flag = true;
            }
        }
        if (!flag) break;
    }
    if (n == i){
        puts("-1");
    } else if (d[n] == INF){
        puts("-2");
    } else {
        printf("%d\n", d[n]);
    }
    return 0;
}
