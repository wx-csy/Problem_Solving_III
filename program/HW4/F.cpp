#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
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
    int cap, flow;
    LL cost;
};

const LL INF = LLONG_MAX / 2;
const int MAXN = 205;
struct MCMF {
    int s, t, n, m;
    vector<edge> edges;
    vector<int> G[MAXN];
    bool inq[MAXN]; // queue
    LL d[MAXN];     // distance
    int p[MAXN];    // previous
    int a[MAXN];    // improvement

    void add_edge(int from, int to, int cap, LL cost) {
        edges.push_back(edge{from, to, cap, 0, cost});
        edges.push_back(edge{to, from, 0, 0, -cost});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool spfa(){
        queue<int> q;
        fill(d, d + MAXN, INF); d[s] = 0;
        memset(inq, 0, sizeof(inq));
        q.push(s); inq[s] = true;
        p[s] = 0; a[s] = INT_MAX;
        while (!q.empty()){
            int u = q.front(); q.pop(); inq[u] = false;
            rep (i, G[u].size()){
                edge& e = edges[G[u][i]];
                if (e.cap > e.flow && d[e.to] > d[u] + e.cost){
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if (!inq[e.to]) q.push(e.to), inq[e.to] = true;
                }
            }
        }
        return d[t] != INF;
    }

    void augment(){
        int u = t;
        while (u != s){
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -= a[t];
            u = edges[p[u]].from;
        }
    }

    int min_cost(int s, int t, LL& cost) {
        this->s = s; this->t = t;
        int flow = 0;
        cost = 0;
        while (spfa()) {
            augment();
            flow += a[t]; cost += a[t] * d[t];
        }
        return flow;
    }
};

int n, m;
char str[128];
int main(){
    typedef pair<int, int> pii;
    while (cin >> n >> m, n){
        vector<pii> p1, p2;
        MCMF mcmf;
        for (int i=0; i<n; i++){
            cin >> str;
            for (int j=0; j<m; j++){
                if (str[j] == 'H'){
                    p1.pb(mp(i, j));
                } else if (str[j] == 'm'){
                    p2.pb(mp(i, j));
                }
            }
        }
        int p = p1.size();
        assert(p1.size() == p2.size());
#define SRC 0
#define DEST 1
#define PIN(x) ((x)+2)
#define POUT(x) ((x)+p+2)
        for (int i=0; i<p; i++){
            for (int j=0; j<p; j++){
                mcmf.add_edge(P1(i), P2(j), 1, abs(p1[i].first - p2[j].first) + abs(p1[i].second - p2[j].second));
            }
        }
        for (int i=0; i<p; i++){
            mcmf.add_edge(0, P1(i), 1, 0);
            mcmf.add_edge(P2(i), 1, 1, 0);
        }
        LL cost;
        mcmf.min_cost(0, 1, cost);
        cout << cost << endl;
    }
    return 0;
}
