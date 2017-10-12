#include <iostream>
#include <algorithm>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
#define pb push_back
#define mt make_tuple
typedef long long LL;
const int MAXV = 105;
const int MAXE = 10005;

int n, m;
struct edge{
    int u, v, w;
    bool operator < (const edge& e) const {
        return w < e.w;
    }
} edges[MAXE];

int p[MAXV];
void init(int num){
    for (int i=1; i<=num; i++) p[i] = i;
}

int parent(int x){
    if (p[x] == x) return x;
    return p[x] = parent(p[x]);
}

bool unite(int u, int v){
    u = parent(u); v = parent(v);
    p[u] = v; return u != v;
}

LL tot;
void kruskal(){
    init(n);
    sort(edges, edges + m);
    int curn = 1;
    tot = 0;
    for (int i = 0; curn < n; i++){
        if (unite(edges[i].u, edges[i].v)){
            tot += edges[i].w;// choose the i-th edge
            curn++;
        }
    }
    cout << tot << endl;
}

int mat[MAXV][MAXV];

int main(){
    ios::sync_with_stdio(false);    cin.tie(0);
    while (cin >> n){
        m = 0;
        int t;
        for (int i=1; i<=n; i++)
            for (int j=1; j<=n; j++){
                cin >> t;
                edges[m].u = i;
                edges[m].v = j;
                edges[m].w = t;
                m++;
            }
        kruskal();
    }
    return 0;
}
