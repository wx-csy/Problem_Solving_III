#include <cstdio>
#include <climits>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cassert>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
#define pb push_back
#define mt make_tuple
#define read(x) scanf("%d", &(x))
typedef long long LL;

int n, k;
struct pt{int id, x, y;};
typedef vector<pt>:: iterator vit;
vector<pt> pts;

struct edge{
    int u, v, w;
    bool operator < (const edge& e) const {
        return w < e.w;
    }
};
vector<edge> edges;

struct BIT{
    inline int lowbit(int x) {return x&-x;}
    int N;
    vector<int> tr;
    vector<int> minv;

    BIT(int n){
        tr.resize(N = n + 5);
        minv.resize(N);
        fill(range(tr), INT_MAX);
    }

    int prefmin(int n, int& x){
        LL ans = INT_MAX;
        int v = 0;
        while (n){
            if (tr[n] < ans){
                ans = tr[n];
                v = minv[n];
            }
            n -= lowbit(n);
        }
        x = ans;
        return v;
    }

    void insert(int n, int v, int x){
        while (n < N){
            if (tr[n] > x){
                tr[n] = x;
                minv[n] = v;
            }
            n += lowbit(n);
        }
    }
};

struct CMP{
    inline bool operator ()(const pt& lhs, const pt& rhs){
        if (lhs.x == rhs.x) return lhs.y > rhs.y;
        return lhs.x > rhs.x;
    }
} cmp;

const int DIFF = 1020;
void make_edge(){
    sort(range(pts), cmp);
    BIT bit(2040);
    for (vit it = pts.begin(); it != pts.end(); it++){
        int vxy;
        int v = bit.prefmin(it->x - it->y + DIFF, vxy);
        if (v) edges.push_back(edge{it->id, v, vxy - it->x - it->y});
        bit.insert(it->x - it->y + DIFF, it->id, it->x + it->y);
    }
}

struct UFS{
    int p[10005];
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
    ufs.init(n);
    sort(range(edges));
    int rem = n - k;
    int ans = 0;
    for (vector<edge>::iterator it = edges.begin(); rem; it++){
        if (ufs.unite(it->u, it->v)){
            ans = max(ans, it->w);
            rem--;
        }
    }
    printf("%d\n", ans);
}

int main(){
    read(n); read(k);
    Rep (i, n) {
        pt p; p.id = i;
        read(p.x); read(p.y);
        pts.push_back(p);
    }
    make_edge();
    for (vit it = pts.begin(); it != pts.end(); it++) swap(it->x, it->y);
    make_edge();
    for (vit it = pts.begin(); it != pts.end(); it++) it->x = -it->x;
    make_edge();
    for (vit it = pts.begin(); it != pts.end(); it++) swap(it->x, it->y);
    make_edge();
    // for (vit it = pts.begin(); it != pts.end(); it++) it->y = -it->y;
    kruskal();
    return 0;
}
