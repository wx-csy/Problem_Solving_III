#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;

struct edge{
    int from, to;
    int cap, flow;
};

const int MAXN = 16;
struct Dinic {
  int n, m, s, t;
  vector<edge> edges;
  vector<int> G[MAXN];
  bool vis[MAXN];
  int d[MAXN];
  int cur[MAXN];

  void add_edge(int from, int to, int cap) {
    edges.push_back((edge){from, to, cap, 0});
    edges.push_back((edge){to, from, 0, 0});
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

  int dfs(int x, int a) {
    if(x == t || a == 0) return a;
    int flow = 0, f;
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

  int max_flow(int s, int t) {
    this->s = s; this->t = t;
    int flow = 0;
    while(bfs()) {
      memset(cur, 0, sizeof(cur));
      flow += dfs(s, INT_MAX);
    }
    return flow;
  }
};

int main(){
    int T; cin >> T;
    Rep (t, T){
        int n, m;
        Dinic dinic;
        cin >> n >> m;
        while (m--){
            int x, y, c;
            cin >> x >> y >> c;
            dinic.add_edge(x, y, c);
        }
        printf("Case %d: %d\n", t, dinic.max_flow(1, n));
    }
    return 0;
}
