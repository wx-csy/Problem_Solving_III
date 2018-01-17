#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x)  (x).begin(), (x).end()
typedef unsigned long long LL;

    struct edge{
        int from, to;
        LL cap, flow;
    };

    const int MAXN = 60005;
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

        void add_arc(int from, int to, LL cap){
            add_edge(from, to, cap);
            add_edge(to, from, cap);
        }

        bool bfs() {
            memset(vis, 0, sizeof(vis));
            queue<int> q;
            q.push(s);
            vis[s] = 1;
            d[s] = 0;
            while (!q.empty()) {
                int x = q.front(); q.pop();
                for (int i = 0; i < G[x].size(); i++) {
                    edge& e = edges[G[x][i]];
                    if (!vis[e.to] && e.cap > e.flow) {
                        vis[e.to] = 1;
                        d[e.to] = d[x] + 1;
                        q.push(e.to);
                    }
                }
            }
            return vis[t];
        }

        LL dfs(int x, LL a) {
            if (x == t || a == 0) return a;
            LL flow = 0, f;
            for (int& i = cur[x]; i < G[x].size(); i++) {
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
            while (bfs()) {
                memset(cur, 0, sizeof(cur));
                flow += dfs(s, LLONG_MAX);
            }
            return flow;
        }
/*
        vector<int> min_cut() { // call this after maxflow
            vector<int> ans;
            for (int i = 0; i < edges.size(); i++) {
                edge& e = edges[i];
                if(vis[e.from] && !vis[e.to] && e.cap > 0) ans.push_back(i);
            }
            return ans;
        }
*/
    } g;

#define BLOCK(x, y) (id(x, y)+10)

int n, m;

inline int id(int i, int j){
    return i * m + j;
}

inline bool valid(int i, int j){
    return i>=0 && i<n && j>=0 && j<m;
}

void build(){
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if(valid(i-1, j)) g.add_arc(BLOCK(i-1, j), BLOCK(i, j), 1);
            if(valid(i+1, j)) g.add_arc(BLOCK(i+1, j), BLOCK(i, j), 1);
            if(valid(i, j+1)) g.add_arc(BLOCK(i, j+1), BLOCK(i, j), 1);
            if(valid(i, j-1)) g.add_arc(BLOCK(i, j-1), BLOCK(i, j), 1);
        }
    }
}

char str[1005];

int main(){
    cin >> n >> m;
    assert(n >= 1 && n <= 50 && m >= 1 && m <= 1000);
    build();
    for (int i=0; i<n; i++){
        cin >> str;
        for (int j=0; j<m; j++){
            if (str[j] == 'H') g.add_edge(0, BLOCK(i, j), INT_MAX);
            if (str[j] == 'X') g.add_edge(BLOCK(i, j), 1, INT_MAX);
        }
    }
    cout << g.max_flow(0, 1) / 2 << endl;
    return 0;
}
