#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;

struct edge{
    int from, to;
    LL cap, flow;
};

const int MAXN = 55555;
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

    vector<int> min_cut() { // call this after maxflow
        vector<int> ans;
        for(int i = 0; i < edges.size(); i++) {
            edge& e = edges[i];
            if(vis[e.from] && !vis[e.to] && e.cap > 0) ans.push_back(i);
        }
        return ans;
    }
};

int main(){
    int n, m;
    #define L(x) ((x)+2)
    #define R(x) ((x)+2+m)
    while (~scanf("%d%d", &n, &m)){
        Dinic dinic;
        LL sum = 0;
        rep (i, n){
            int c; scanf("%d", &c);
            dinic.add_edge(R(i), 1, c);
        }
        rep (i, m){
            int x, y, c; scanf("%d%d%d", &x, &y, &c);
            sum += c;
            dinic.add_edge(0, L(i), c);
            dinic.add_edge(L(i), R(x-1), LLONG_MAX);
            dinic.add_edge(L(i), R(y-1), LLONG_MAX);
        }
        cout << sum - dinic.max_flow(0, 1) << endl;
    }
    return 0;
}
