#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x)  (x).begin(), (x).end()
typedef unsigned long long LL;

    const int INF = 0x7f7f7f7f;
    const int MAXV = 300005;
    const int MAXE = 1000005;
    struct edge{int u, v, w;};

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

        void add_double_edge(int u, int v, int w) {
            add_edge(u, v, w);
            add_edge(v, u, w);
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
    } g;

int sn[30005];
int acc[30005];
int cost[30005];

int n, m;

#define CENTER(i) i
#define STATION(v, i) (acc[v-1] + i + 30005)

int main(){
    scanf("%d%d", &n, &m);
    Rep (i, n) scanf("%d", &sn[i]), acc[i] = acc[i-1] + sn[i];
    Rep (i, n) scanf("%d", &cost[i]);
    Rep (i, n) Rep (j, sn[i])
        g.add_edge(STATION(i, j), CENTER(i), cost[i]);

    rep (i, m) {
        int u, ii, v, jj, c;
        scanf("%d%d%d%d%d", &u, &ii, &v, &jj, &c);
        g.add_double_edge(STATION(u, ii), STATION(v, jj), c);
        g.add_edge(CENTER(u), STATION(v, jj), c);
        g.add_edge(CENTER(v), STATION(u, ii), c);
    }
    g.V = 300003;
    g.dijkstra(STATION(1, 1));
    int ans = INT_MAX;
    Rep (i, sn[n]) {
       // printf("reg %d, stat %d, id = %d, time = %d\n", i, n, STATION(n, i), g.d[STATION(n, i)]);
        ans = min(ans, g.d[STATION(n, i)]);
    }
    printf("%d\n", ans);
    return 0;
}
