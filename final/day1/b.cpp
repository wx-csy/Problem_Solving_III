#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x)  (x).begin(), (x).end()
typedef long long LL;

 // I have no Hopcroft-Karp template !!!

    struct edge{
        int from, to;
        int cap, flow;
        LL cost;
    };

    const LL INF = LLONG_MAX / 2;
    const int MAXN = 5005;
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

    #ifdef GIVEN_FLOW
        bool min_cost(int s, int t, int f, LL& cost) {
            this->s = s; this->t = t;
            int flow = 0;
            cost = 0;
            while (spfa()) {
                augment();
                if (flow + a[t] >= f){
                    cost += (f - flow) * a[t]; flow = f;
                    return true;
                } else {
                    flow += a[t]; cost += a[t] * d[t];
                }
            }
            return false;
        }
    #else
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
    #endif
    } g;



#define ACTION(i) (i + 5)
#define TIM(i) (i+1000)

int n;

vector<int> t;
int vf[1004],  vt[1005], vv[1005];
vector<pair<int, int> > vp;
map<int, int> mt;
LL ans = 0;
int main(){
    cin >> n;
    for (int i=0; i<n; i++){
        int ss, tt, v;
        cin >> ss >> tt >> v;
        if (tt-ss >= 1000) {
                ans += v;
        continue;
        }
        tt++;
        t.push_back(ss);
        t.push_back(tt);
        vf[i] = ss;
        vt[i] = tt;
        vv[i] = v;
    }
    sort(range(t));
    int un = unique(range(t)) - t.begin();
    for (int i=0; i<un; i++){
        mt[t[i]] = i;
    }
    for (int i=0; i<n; i++){
        g.add_edge(1, ACTION(i), 1, 0);
        for (int tt = mt[vf[i]]; tt < mt[vt[i]]; tt++){
            g.add_edge(ACTION(i), TIM(tt), 1, -vv[i]);
        }
    }
    for (int i=0; i<un-1; i++){
        g.add_edge(TIM(i), 2, t[i+1]-t[i], 0);
    }
    LL c = 0;
    g.min_cost(1, 2, c);
    cout << -c + ans << endl;
    return 0;
}
