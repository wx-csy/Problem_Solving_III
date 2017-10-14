#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <climits>
#include <cstring>
#include <queue>
#include <utility>
#include <stack>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair

typedef long long LL;

#define LL int
struct edge{
    int from, to;
    LL cap, flow;
};

int n, m, k;

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

    bool unique_dfs(int u, int f){
        vis[u] = 1;
        rep (i, G[u].size()){
            edge& e = edges[G[u][i]];
            if (e.to != f && e.cap > e.flow &&
                (vis[e.to] || unique_dfs(e.to, u)))
               return true;
        }
        vis[u] = 0;
        return false;
    }

    bool is_unique(){
        memset(vis, 0, sizeof vis);
        rep (i, G[s].size()){
            edge& e = edges[G[s][i]];
            if (unique_dfs(e.to,  -1))
               return false;
        }
        return true;
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

int ans[405][405];
int main(){
    while (cin >> n >> m >> k){
        #define ROW(i) ((i)+2)
        #define COL(i) ((i)+2+n)
        #define SRC 0
        #define SINK 1
        Dinic dinic;
        int sum1 = 0, sum2 = 0;
        bool imp = false;
        for (int i=0; i<n; i++){
            int x; cin >> x; sum1 += x;
            dinic.add_edge(SRC, ROW(i), x);
        }
        for (int i=0; i<m; i++){
            int x; cin >> x; sum2 += x;
            dinic.add_edge(COL(i), SINK, x);
        }
        if (sum1 != sum2){
            cout << "Impossible" << endl; continue;
        }
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                dinic.add_edge(ROW(i), COL(j), k);
        if (dinic.max_flow(SRC, SINK) != sum1){
            cout << "Impossible" << endl;
        } else {
            if (dinic.is_unique()){
                cout << "Unique" << endl;
                for (int i=0; i<dinic.edges.size(); i+=2){
                    edge& e = dinic.edges[i];
                    if (e.from >= 2 && e.from < 2+n &&
                        e.to >= 2 + n && e.to < 2+n+m){
                        ans[e.from-2][e.to-2-n] = e.flow;
                    }
                }
                for (int i=0; i<n; i++){
                    for (int j=0; j<m; j++){
                        cout << ans[i][j];
                        if (j != m-1) cout << ' ';
                    } cout << endl;
                }
            } else {
                cout << "Not Unique" << endl;
            }
        }
    }
    return 0;
}
