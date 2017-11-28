#include <iostream>
#include <complex>
#include <string>
#include <cmath>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
typedef long long LL;

const int NMAX = 1<<17;
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

int n;
string a, b;
cplx x[NMAX], y[NMAX];
int z[NMAX];

int main(){
    while (cin >> a >> b) {
        int k = 32 - __builtin_clz(a.size()+b.size()+1);
        for (int i=0; i<(1<<k); i++) x[i]=y[i]=0;
        Rep (i, a.size()) x[a.size()-i] = a[i-1] - '0';
        Rep (i, b.size()) y[b.size()-i] = b[i-1] - '0';
        FFT fft(k);
        fft.conv(x, y);
        rep (i, 1<<k) z[i] = real(x[i]) + 0.5;
        int dc = (1<<k)-1;
        int c = 0;
        rep (i, (1<<k)) {
            z[i] += c;
            c = z[i] / 10;
            z[i] %= 10;
        }
        while (dc && z[dc]==0) dc--;
        while (dc >= 0) cout << z[dc--];
        cout << endl;
    }
    return 0;
}
