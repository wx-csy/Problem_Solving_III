#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <queue>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()

const int INF = 0x7f7f7f7f;
const int MAXV = 1005;
const int MAXE = 500005;
struct edge{
    int u, v, w;
};

struct graph{
    int V;
    vector<edge> adj[MAXV];
    int d[MAXV];
    edge* p[MAXV];

    void add_edge(int u, int v, int w){
        edge e;
        e.u = u; e.v = v; e.w = w;
        adj[u].push_back(e);
    }

    bool done[MAXV];
    void dijkstra(int src){
        typedef pair<int,int> pii;
        priority_queue<pii, vector<pii>, greater<pii> > q;

        fill(d, d + V + 1, INF);
        d[src] = 0;
        fill(done, done + V + 1, false);
        q.push(make_pair(0, src));
        while (!q.empty()){
            int u = q.top().second; q.pop();
            if (done[u]) continue;
            done[u] = true;
            rep (i, adj[u].size()){
                edge e = adj[u][i];
                if (d[e.v] > d[u] + e.w){
                    d[e.v] = d[u] + e.w;
                    p[e.v] = &adj[u][i];
                    q.push(make_pair(d[e.v], e.v));
                }
            }
        }
    }
};

int t, s, d;
int main(){
    while (~scanf("%d%d%d", &t, &s, &d)){
        graph g;
        g.V = 1001;
        int a, b, wt;
        while (t--){
            scanf("%d%d%d", &a, &b, &wt);
            g.add_edge(a, b, wt);
            g.add_edge(b, a, wt);
        }
        rep (i, s){
            scanf("%d", &a);
            g.add_edge(1001, a, 0);
        }
        g.dijkstra(1001);
        int ans = INT_MAX;
        rep (i, d){
            scanf("%d", &a);
            ans = min(ans, g.d[a]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
