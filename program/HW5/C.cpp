#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;

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

int n, m;
double resi[64][64];

int main(){
    int T; cin >> T;
    Rep (t, T){
        cin >> n >> m;
        memset(resi, 0, sizeof(resi));
        rep (i, m){
            int u, v; double r;
            cin >> u >> v >> r;
            resi[u-1][v-1] += 1/r; resi[v-1][u-1] += 1/r;
        }
        VVT a, b;
        a.resize(n); b.resize(n);
        rep (i, n){
            a[i].resize(n); b[i].resize(1);

            if (i == 0) a[0][0] = 1, b[0][0] = 0;
            else if(i == n-1) a[n-1][n-1] = 1, b[n-1][0] = 1;
            else {
                double t = 0;
                for (int j=0; j<n; j++) if (i != j) t += resi[i][j];
                for (int j=0; j<n; j++) if (i != j) a[i][j] = resi[i][j];
                a[i][i] = -t;
            }
        }

        GaussJordan(a, b);
        double totcur  =  0;
        for (int i=0; i<n-1; i++){ totcur += (b[n-1][0] - b[i][0]) * resi[i][n-1]; }
        printf("Case #%d: %.2f\n", t, b[n-1][0] / totcur);
    }
    return 0;
}
