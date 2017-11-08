#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

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

int main(){
    int T; cin >> T;
    int n;
    int r[24], a[24];

    for (int i=0; i<24; i++) c[i] = -1;
    for (int i=0; i<24; i++){
        for (int j=0; j<8; j++){
            A[(i+j)%24][i] = -1;
        }
        A[i+24][i] = 1;
    }

    while (T--){
        memset(a, 0, sizeof(a));
        for (int i=0; i<24; i++) cin >> b[i];
        for (int i=0; i<24; i++) b[i] = -b[i];
        cin >> n;
        for (int i=0; i<n; i++){
            int tm; cin >> tm;
            a[tm]++;
        }
        for (int i=0; i<24; i++) b[i+24] = a[i];
/*
        for (int i=0; i<48; i++){
        for (int j=0; j<24; j++){
            cout << A[i][j] << ' ';
        }cout << " : " << b[i] <<endl;
    }*/

        double ans = simplex(48, 24);

        if (ans > 0) cout << "No Solution" << endl;
        else cout << int(-ans + 0.5) << endl;
    }
    return 0;
}
