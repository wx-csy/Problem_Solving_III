#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstring>
#include <stack>
#include <climits>
#include <cstdio>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
#define pb push_back
#define mt make_tuple
typedef long long LL;

#define int LL
const int MAXV = 100005;
struct graph{
    vector<int> adj[MAXV];
    stack<int> s;
    int V; // number of vertices
    int pre[MAXV], lnk[MAXV], scc[MAXV];
    int time, sccn;
    vector<int> adjc[MAXV];
    int indeg[MAXV], outdeg[MAXV], sz[MAXV];

    void init(){
        assert(s.empty());
        Rep (i, V){
            adj[i].clear();
            indeg[i] = outdeg[i] = sz[i] = 0;
        }
    }

    void add_edge(int u, int v){
        adj[u].push_back(v);
    }

    void dfs(int u){
        pre[u] = lnk[u] = ++time;
        s.push(u);
        rep (i, adj[u].size()){
            int v = adj[u][i];
            if (!pre[v]){
                dfs(v);
                lnk[u] = min(lnk[u], lnk[v]);
            } else if (!scc[v]){
                lnk[u] = min(lnk[u], pre[v]);
            }
        }
        if (lnk[u] == pre[u]){
            sccn++;
            int x;
            do {
                x = s.top(); s.pop();
                scc[x] = sccn;
            } while (x != u);
        }
    }

    void find_scc(){
        time = sccn = 0;
        memset(scc, 0, sizeof(scc));
        memset(pre, 0, sizeof(pre));
        Rep (i, V){
            if (!pre[i]) dfs(i);
        }
    }


    void contract(){
        Rep (i, V){
            sz[scc[i]]++;
            rep (j, adj[i].size()){
                if (scc[i] != scc[adj[i][j]]){
                    adjc[scc[i]].push_back(scc[adj[i][j]]);
                    indeg[scc[i]]++; outdeg[scc[adj[i][j]]]++;
                }
            }
        }
    }

    LL solve(){
        LL msz = LLONG_MAX; int id;
        Rep (i, sccn){
            if ((indeg[i] == 0 || outdeg[i] == 0) && sz[i] < msz){
                msz = sz[id = i];
            }
        }
        return msz * (V - msz);
    }
} g;

#undef int
int main(){
#define int LL
    int T; scanf("%I64d", &T);
    for (int t=1; t<=T; t++){
        g.init();
        int E;
        scanf("%I64d%I64d", &g.V, &E);
        rep (i, E){
            int u, v; scanf("%I64d%I64d", &u, &v);
            g.add_edge(u, v);
        }
        g.find_scc();
        g.contract();
        if (g.sccn == 1){
            printf("Case %I64d: -1\n", t);
            continue;
        }
        LL ans = (LL)(g.V) * (g.V - 1) - g.solve() - E;
        printf("Case %I64d: %I64d\n", t, ans);
    }
    return 0;
}
