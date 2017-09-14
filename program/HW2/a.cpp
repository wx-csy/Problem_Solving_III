#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <queue>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()

typedef pair<int ,int > cost;

cost operator + (const cost& lhs, const cost& rhs){
    return cost(lhs.first + rhs.first, lhs.second+rhs.second);
}

const int INF = 0x7f7f7f7f;
const int MAXV = 10005;
const int MAXE = 500005;
struct edge{
    int u, v;
    cost w;
};

struct graph{
    int V;
    vector<edge> adj[MAXV];
    cost d[MAXV];

    void add_edge(int u, int v, cost w){
        edge e;
        e.u = u; e.v = v; e.w = w;
        adj[u].push_back(e);
    }

    bool done[MAXV];
    void dijkstra(int src){
        typedef pair<cost, int> pii;
        priority_queue<pii, vector<pii>, greater<pii> > q;

        fill(d, d + V + 1, cost(INF, INF));
        d[src] = cost(0, 0);
        fill(done, done + V + 1, false);
        q.push(make_pair(cost(0, 0), src));
        while (!q.empty()){
            int u = q.top().second; q.pop();
            if (done[u]) continue;
            done[u] = true;
            rep (i, adj[u].size()){
                edge e = adj[u][i];
                if (d[e.v] > d[u] + e.w){
                    d[e.v] = d[u] + e.w;
                    q.push(make_pair(d[e.v], e.v));
                }
            }
        }
    }
};

int n, m, s, t;
int main(){
    while(true){
        graph g;
        scanf("%d%d", &n, &m);
        if (n==0 && m==0) break;
        g.V = n;
        while(m--){
            int a, b, d, p;
            scanf("%d%d%d%d", &a, &b, &d, &p);
            g.add_edge(a, b, cost(d, p));
            g.add_edge(b, a, cost(d, p));
        }
        scanf("%d%d", &s, &t);
        g.dijkstra(s);
        printf("%d %d\n", g.d[t].first, g.d[t].second);
    }
    return 0;
}
