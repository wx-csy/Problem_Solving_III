namespace SCC {
    const int MAXV = 100005;

    struct graph{
        vector<int> adj[MAXV];
        stack<int> s;
        int V; // number of vertices
        int pre[MAXV], lnk[MAXV], scc[MAXV];
        int time, sccn;

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

        vector<int> adjc[MAXV];
        void contract(){
            Rep (i, V)
                rep (j, adj[i].size()){
                    if (scc[i] != scc[adj[i][j]])
                        adjc[scc[i]].push_back(scc[adj[i][j]]);
                }
        }
    };


}

namespace FLOYD {
    const LL INF = LLONG_MAX / 2;
    const int MAXV = 1005;
    int V;
    LL d[MAXV][MAXV];

    void init(){
        Rep (i, V){
            Rep (j, V) d[i][j] = INF;
            d[i][i] = 0;
        }
    }

    void floyd(){
        Rep (k, V)
            Rep (i, V)
                Rep (j, V)
                    // ! (*) if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }

}

namespace DIJKSTRA { // including spfa
// #define DIJKSTRA
// #define SPFA
    const int INF = 0x7f7f7f7f;
    const int MAXV = 10005;
    const int MAXE = 500005;
    struct edge{
        int u, v, w;
    };

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

#ifdef DIJKSTRA
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
        }
#elif defined SPFA
        bool inq[MAXV];
        void spfa(int src){
            queue<int> q;
            fill(d, d + V + 1, INF);
            d[src] = 0;
            fill(inq, inq + V + 1, false);
            q.push(src); inq[src] = true;
            while (!q.empty()){
                int u = q.front(); q.pop(); inq[u] = false;
                rep (i, adj[u].size()){
                    edge e = adj[u][i];
                    if (d[e.v] > d[u] + e.w){
                        d[e.v] = d[u] + e.w;
                        p[e.v] = &adj[u][i];
                        if (!inq[e.v])
                            q.push(e.v), inq[e.v] = true;
                    }
                }
            }
        }
#endif
    };
}

namespace DINIC {
    struct edge{
        int from, to;
        LL cap, flow;
    };

    const int MAXN = 1005;
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

        vector<int> min_cut() { // call this after maxflow
            vector<int> ans;
            for (int i = 0; i < edges.size(); i++) {
                edge& e = edges[i];
                if(vis[e.from] && !vis[e.to] && e.cap > 0) ans.push_back(i);
            }
            return ans;
        }
    };

}

namespace MAX_FLOW_MIN_COST {
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
    };

}

namespace HUNGARIAN {

    struct Hungarian{
        int nx, ny;
        vector<int> mx, my;
        vector<vector<int> > e;
        vector<bool> mark;

        void init(int nx, int ny){
            this->nx = nx;
            this->ny = ny;
            mx.resize(nx); my.resize(ny);
            e.clear(); e.resize(nx);
            mark.resize(nx);
        }

        inline void add(int a, int b){
            e[a].push_back(b);
        }

        bool augment(int i){
            if (!mark[i]) {
                mark[i] = true;
                for (int j : e[i]){
                    if (my[j] == -1 || augment(my[j])){
                        mx[i] = j; my[j] = i;
                        return true;
                    }
                }
            }
            return false;
        }

        int match(){
            int ret = 0;
            fill(range(mx), -1);
            fill(range(my), -1);
            rep (i, nx){
                fill(range(mark), false);
                if (augment(i)) ret++;
            }
            return ret;
        }
    };

}

namespace LINEAR_EQUATION {
    /*
        Uses:
            (1) Solving systems of linear equations (AX = B)
            (2) Inverting matrices (AX = I)
            (3) Computing determinants of square matrices

        Running time: O(n^3)

        Input:  a[][] = an n*n invertible matrix
                b[][] = an n*m matrix

        Output: X     = an n*m matrix (stored in b[][])
                A^-1  = an n*n matrix (stored in a[][])
                returns determinant of a[][]
    */

    const double EPS = 1e-10;

    typedef double T;
    typedef vector<int> VI;
    typedef vector<T> VT;
    typedef vector<VT> VVT;

    T GaussJordan(VVT &a, VVT &b) {
        const int n = a.size();
        const int m = b[0].size();
        VI irow(n), icol(n), ipiv(n);
        T det = 1;

        for (int i = 0; i < n; i++) {
            int pj = -1, pk = -1;
            for (int j = 0; j < n; j++) if (!ipiv[j])
                for (int k = 0; k < n; k++) if (!ipiv[k])
                    if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk])) { pj = j; pk = k; }
            if (fabs(a[pj][pk]) < EPS) { return 0; }
            ipiv[pk]++;
            swap(a[pj], a[pk]);
            swap(b[pj], b[pk]);
            if (pj != pk) det *= -1;
            irow[i] = pj;
            icol[i] = pk;

            T c = 1.0 / a[pk][pk];
            det *= a[pk][pk];
            a[pk][pk] = 1.0;
            for (int p = 0; p < n; p++) a[pk][p] *= c;
            for (int p = 0; p < m; p++) b[pk][p] *= c;
            for (int p = 0; p < n; p++) if (p != pk) {
                c = a[p][pk];
                a[p][pk] = 0;
                for (int q = 0; q < n; q++) a[p][q] -= a[pk][q] * c;
                for (int q = 0; q < m; q++) b[p][q] -= b[pk][q] * c;
            }
        }

        for (int p = n-1; p >= 0; p--) if (irow[p] != icol[p])
            for (int k = 0; k < n; k++) swap(a[k][irow[p]], a[k][icol[p]]);

        return det;
    }

}

namespace SIMPLEX {

    /*
        max cx
        s.t. Ax <= b, x >= 0
    */

    const int MAXN = 100, MAXM = 100;
    //	`here MAXN is the MAX number of conditions, MAXM is the MAX number of vars`
    const double EPS = 1e-10;

    int avali[MAXM], avacnt;
    double A[MAXN][MAXM];
    double b[MAXN], c[MAXM];
    double simplex(int n, int m) {
    //	`here n is the number of conditions, m is the number of vars`
        m++;
        int r = n, s = m - 1;
        static double D[MAXN + 2][MAXM + 1];
        static int ix[MAXN + MAXM];
        memset(D, 0, sizeof(D));
        memset(ix, 0, sizeof(ix));

        for (int i = 0; i < n + m; i++) ix[i] = i;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m - 1; j++) D[i][j] = -A[i][j];
            D[i][m - 1] = 1;
            D[i][m] = b[i];
            if (D[r][m] > D[i][m]) r = i;
        }
        for (int j = 0; j < m - 1; j++) D[n][j] = c[j];
        D[n + 1][m - 1] = -1;
        for (double d; ; ) {
            if (r < n) {
                int t = ix[s]; ix[s] = ix[r + m]; ix[r + m] = t;
                D[r][s] = 1.0 / D[r][s];
                for (int j = 0; j <= m; j++) if (j != s) D[r][j] *= -D[r][s];
                avacnt = 0;
                for (int i = 0; i <= m; ++i)
                    if(fabs(D[r][i]) > EPS)
                        avali[avacnt++] = i;
                for (int i = 0; i <= n + 1; i++) if (i != r) {
                    if(fabs(D[i][s]) < EPS) continue;
                    double *cur1 = D[i], *cur2 = D[r], tmp = D[i][s];
                    //for (int j = 0; j <= m; j++) if (j != s) cur1[j] += cur2[j] * tmp;
                    for(int j = 0; j < avacnt; ++j) if(avali[j] != s) cur1[avali[j]] += cur2[avali[j]] * tmp;
                    D[i][s] *= D[r][s];
                }
            }
            r = -1; s = -1;
            for (int j = 0; j < m; j++) if (s < 0 || ix[s] > ix[j]) {
                if (D[n + 1][j] > EPS || D[n + 1][j] > -EPS && D[n][j] > EPS) s = j;
            }
            if (s < 0) break;
            for (int i = 0; i < n; i++) if (D[i][s] < -EPS) {
                if (r < 0 || (d = D[r][m] / D[r][s] - D[i][m] / D[i][s]) < -EPS
                          || d < EPS && ix[r + m] > ix[i + m])
                    r = i;
            }
            if (r < 0) return 1; // `非有界`
        }
        if (D[n + 1][m] < -EPS) return 1; // `无法执行`
        static double x[MAXM - 1];
        memset(x, 0, sizeof(x));
        for (int i = m; i < n + m; i++) if (ix[i] < m - 1) x[ix[i]] = D[i - m][m];
        return D[n][m];
    }
}

namespace FFT {
    const int NMAX = 1<<20;
    typedef complex<double> cplx;
    const double PI = 2*acos(0.0);
    struct FFT{
        int rev[NMAX];
        cplx omega[NMAX], oinv[NMAX];
        int K, N;

        FFT(int k){
            K = k; N = 1 << k;
            rep (i, N){
                rev[i] = (rev[i>>1]>>1) | ((i&1)<<(K-1));
                omega[i] = polar(1.0, 2.0 * PI / N * i);
                oinv[i] = conj(omega[i]);
            }
        }

        void dft(cplx* a, cplx* w){
            rep (i, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
            for (int l = 2; l <= N; l *= 2){
                int m = l/2;
                for (cplx* p = a; p != a + N; p += l)
                    rep (k, m){
                        cplx t = w[N/l*k] * p[k+m];
                        p[k+m] = p[k] - t; p[k] += t;
                    }
            }
        }

        void fft(cplx* a){dft(a, omega);}
        void ifft(cplx* a){
            dft(a, oinv);
            rep (i, N) a[i] /= N;
        }

        void conv(cplx* a, cplx* b){
            fft(a); fft(b);
            rep (i, N) a[i] *= b[i];
            ifft(a);
        }
    };

}

namespace NUMBER_THEORY_GEN {
    LL powmod(LL b, unsigned long long e, LL m){
        LL r = 1;
        while (e){
            if (e & 1) r = r * b % m;
            b = b * b % m;
            e >>= 1;
        }
        return r;
    }

    LL mulmod(LL a, LL b, LL m){
        LL r = 0;
        a %= m; b %= m;
        while(b) {
            if(b & 1) r += a, r %= m;
            b >>= 1;
            if(a < m - a)
                a <<= 1;
            else
                a -= (m - a);
        }
        return r;
    }

    inline LL mathmod(LL a, LL b){
        return (a % b + b) % b;
    }

    void exgcd(LL a, LL b, LL &g, LL &x, LL &y){
        if (!b) g = a, x = 1, y = 0;
        else {
            exgcd(b, a % b, g, y, x),
            y -= x * (a / b);
        }
    }

    LL gcd(LL a, LL b) {return (b>0)?gcd(b,a%b):a;}

    inline LL minv(LL a, LL m){
        LL g, x, y;
        exgcd(a, m, g, x, y);
        return (x % m + m) % m;
    }

    bool Miller_Rabin(LL n){
        if (n < 3) return n==2;
        // ! The array a[] should be modified if the range of x changes.
        const LL a[] = {2LL, 7LL, 61LL, LLONG_MAX};
        LL r = 0, d = n-1, x;
        while (~d & 1) d >>= 1, r++;
        for (int i=0; a[i] < n; i++){
            x = powmod(a[i], d, n);
            if (x == 1 || x == n-1) goto next;
            rep (i, r) {
                x = (x * x) % n;
                if (x == n-1) goto next;
            }
            return false;
    next:;
        }
        return true;
    }

}

namespace SIEVE_OF_ERATOSTHENES {
    const int MAXX = 1e7+5;
    bool p[MAXX];

    void sieve(){
        p[0] = p[1] = 1;
        for (int i = 2; i*i < MAXX; i++) if (!p[i])
            for (int j = i*i; j < MAXX; j+=i) p[j] = true;
    }

}

namespace SIEVE_OF_EULER {
    const int MAXX = 1e7+5;
    bool p[MAXX];
    int prime[MAXX], sz;

    void sieve(){
        p[0] = p[1] = 1;
        for (int i = 2; i < MAXX; i++){
            if (!p[i]) prime[sz++] = i;
            for (int j = 0; j < sz && i*prime[j] < MAXX; j++){
                p[i*prime[j]] = 1;
                if (i % prime[j] == 0) break;
            }
        }
    }

}

namespace INTEGER_FACTORIZATION { // Pollard's rho
    ULL gcd(ULL a, ULL b) {return b ? gcd(b, a % b) : a;}

    ULL PollardRho(ULL n){
        ULL c, x, y, d = n;
        if (~n&1) return 2;
        while (d == n){
            x = y = 2;
            d = 1;
            c = rand() % (n - 1) + 1;
            while (d == 1){
                x = (mulmod(x, x, n) + c) % n;
                y = (mulmod(y, y, n) + c) % n;
                y = (mulmod(y, y, n) + c) % n;
                d = gcd(x-y>0 ? x-y : y-x, n);
            }
        }
        return d;
    }

}

namespace NTT {
    const int NMAX = 1<<21;
    // 998244353 = 7*17*2^23+1, G = 3
    const int P = 1004535809, G = 3; // = 479*2^21+1

    struct NTT{
        int rev[NMAX];
        LL omega[NMAX], oinv[NMAX];
        int g, g_inv; // g: g_n = G^((P-1)/n)
        int K, N;

        LL powmod(LL b, LL e){
            LL r = 1;
            while (e){
                if (e&1) r = r * b % P;
                b = b * b % P;
                e >>= 1;
            }
            return r;
        }

        NTT(int k){
            K = k; N = 1 << k;
            g = powmod(G, (P-1)/N);
            g_inv = powmod(g, N-1);
            omega[0] = oinv[0] = 1;
            rep (i, N){
                rev[i] = (rev[i>>1]>>1) | ((i&1)<<(K-1));
                if (i){
                    omega[i] = omega[i-1] * g % P;
                    oinv[i] = oinv[i-1] * g_inv % P;
                }
            }
        }

        void _ntt(LL* a, LL* w){
            rep (i, N) if (i < rev[i]) swap(a[i], a[rev[i]]);
            for (int l = 2; l <= N; l *= 2){
                int m = l/2;
                for (LL* p = a; p != a + N; p += l)
                    rep (k, m){
                        LL t = w[N/l*k] * p[k+m] % P;
                        p[k+m] = (p[k] - t + P) % P;
                        p[k] = (p[k] + t) % P;
                    }
            }
        }

        void ntt(LL* a){_ntt(a, omega);}
        void intt(LL* a){
            LL inv = powmod(N, P-2);
            _ntt(a, oinv);
            rep (i, N) a[i] = a[i] * inv % P;
        }

        void conv(LL* a, LL* b){
            ntt(a); ntt(b);
            rep (i, N) a[i] = a[i] * b[i] % P;
            intt(a);
        }
    };

}

namespace PERMUTATION {
    typedef vector<int> perm;

    perm operator * (const perm lhs, const perm rhs){
        int sz;
        assert((sz = lhs.size()) == rhs.size());
        perm res; res.resize(sz);
        for (int i=0; i<sz; i++){
            res[i] = rhs[lhs[i]];
        }
        return res;
    }

    perm operator ~ (const perm lhs){
        int sz = lhs.size();
        perm res; res.resize(sz);
        for (int i=0; i<sz; i++){
            res[lhs[i]] = i;
        }
        return res;
    }

    struct permutation{
        int size;
        vector<vector<int>> orbits;

        permutation(perm p){
            size = p.size();
            vector<bool> visited(size);
            for (int i=0; i<size; i++){
                if (visited[i]) continue;
                int cur = i;
                vector<int> orbit;
                while (!visited[cur]){
                    visited[cur] = true;
                    orbit.push_back(cur);
                    cur = p[cur];
                }
                orbits.push_back(move(orbit));
            }
        }
    };

}


