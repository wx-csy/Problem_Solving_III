#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
#define pb push_back
#define mt make_tuple
typedef long long LL;

int s, p;

const int MAXV = 100005;
const int MAXE = 300005;

int n, m;
struct edge{
    int u, v;
    double w;
    bool operator < (const edge& e) const {
        return w < e.w;
    }
} edges[MAXE];

#define p pppp
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
#undef p

void kruskal(){
    init(n);
    sort(edges, edges + m);
    int curn = 1;
    for (int i = 0; curn < n; i++){
        if (unite(edges[i].u, edges[i].v)){
            // choose the i-th edge
            if (curn == p - s){
                printf("%.2f\n", edges[i].w);
                return;
            }
            curn++;

        }
    }
}

typedef pair<double, double> pt;
pt pts[505];

int main(){
    ios::sync_with_stdio(false);    cin.tie(0);
    int N; cin >> N;
    while (N--){
        cin >> s >> p;
        for (int i=1; i<=p; i++){
            cin >> pts[i].first >> pts[i].second;
        }
        n = p;
        m = 0;
        for (int i=1; i<=p; i++){
            for (int j=1; j<=p; j++){
                edges[m].u = i;
                edges[m].v = j;
                edges[m].w = hypot(pts[i].first - pts[j].first,
                                   pts[i].second - pts[j].second);
                m++;
            }
        }
        kruskal();
    }
    return 0;
}
