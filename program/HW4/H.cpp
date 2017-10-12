#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <climits>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair

typedef long long LL;
struct edge{
    int from, to;
    LL cap, flow;
};

const int MAXN = 1005;
struct Dinic {
    int n, m, s, t;
    vector<edge> edges;
    vector<int> G[MAXN];
    bool vis[MAXN];
    int d[MAXN];
    int cur[MAXN];

    void add_edge(int from, int to, LL cap) {
        edges.push_back(edge{from, to, cap, 0});
        edges.push_back(edge{to, from, 0, 0});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool bfs() {
        memset(vis, 0, sizeof(vis));
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        d[s] = 0;
        while(!q.empty()) {
            int x = q.front(); q.pop();
            for(int i = 0; i < G[x].size(); i++) {
                edge& e = edges[G[x][i]];
                if(!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    LL dfs(int x, LL a) {
        if(x == t || a == 0) return a;
        LL flow = 0, f;
        for(int& i = cur[x]; i < G[x].size(); i++) {
            edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (f = dfs(e.to, min(a, e.cap-e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }

    LL max_flow(int s, int t) {
        this->s = s; this->t = t;
        LL flow = 0;
        while(bfs()) {
            memset(cur, 0, sizeof(cur));
            flow += dfs(s, INT_MAX);
        }
        return flow;
    }
};

int n, m;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    for (int t=1; t<=T; t++){
        Dinic dinic;
        cin >> n >> m;
        int u, v, c ,d;
        rep (i, m) {
            cin >> u >> v >> c >> d;
            dinic.add_edge(u, v, c);
            if (d) dinic.add_edge(v, u, c);
        }
        dinic.max_flow(0, n-1);
        Dinic dinic2;
        rep (i, dinic.edges.size()){
            if (dinic.edges[i].cap == 0) continue;
            if (dinic.edges[i].cap == dinic.edges[i].flow){
                dinic2.add_edge(dinic.edges[i].from, dinic.edges[i].to, 1);
            } else {
                dinic2.add_edge(dinic.edges[i].from, dinic.edges[i].to, INT_MAX);
            }
        }
        printf("Case %d: %d\n", t, dinic2.max_flow(0, n-1));
    }
    return 0;
}
