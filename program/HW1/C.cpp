#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
#define pb push_back
#define mt make_tuple
typedef long long LL;

struct edge{
    int u, v, w;

    bool operator < (const edge& lhs) const{
        return w < lhs.w;
    }
};

int n, m;
vector<edge> edges;

struct UFS{
    int p[105];
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
} ufs;

void kruskal(){
    LL tot = 0;
    ufs.init(n);
    sort(range(edges));
    typedef vector<edge>::iterator vit;
    vit itl = edges.begin(), itr;
    while (itl != edges.end()){
        itr = equal_range(range(edges), *itl).second;
        UFS u2; u2.init(n);
        for (vit it = itl; it != itr; it++){
            if (ufs.parent(it->u) == ufs.parent(it->v)) continue;
            if (!u2.unite(ufs.parent(it->u), ufs.parent(it->v))){
                cout << "Not Unique!" << endl;
                return;
            }
        }
        for (vit it = itl; it != itr; it++){
            if (ufs.unite(it->u, it->v)){
                tot += it->w;
            }
        }
        itl = itr;
    }
    cout << tot << endl;
}


int main(){
    ios::sync_with_stdio(false);    cin.tie(0);
    int T; cin >> T;
    while (T--){
        edges.clear();
        cin >> n >> m;
        while (m--){
            edge e;
            cin >> e.u >> e.v >> e.w;
            edges.push_back(e);
        }
        kruskal();
    }
    return 0;
}
