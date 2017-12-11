#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
using namespace std;

typedef long long LL;

LL mulmod(LL a, LL b, LL m){
    LL r = 0; a %= m; b %= m;
    while (b){
        if (b & 1) r += a, r %= m;
        b >>= 1;
        if (a < m - a) a <<= 1;
        else a -= (m - a);
    }
    return r;
}

LL powmod(LL b, LL e, LL m){
    LL r = 1;
    while (e){
        if (e&1) r = mulmod(r, b, m);
        b = mulmod(b, b, m);
        e >>= 1;
    }
    return r;
}

bool test(LL n){
    if (n < 3) return n == 2;
    const LL a[] = {2, 325, 9375, 28178, 450775,
                    9780504, 1795265022, LLONG_MAX};
    LL r = 0, d = n-1, x;
    while (~d & 1) d >>= 1, r++;
    for (int i=0; a[i]<n; i++){
        x = powmod(a[i], d, n);
        if (x==1 || x==n-1) goto next;
        for (int i=0; i<r; i++){
            x = mulmod(x, x, n);
            if (x == n-1) goto next;
        }
        return false;
next:;
    }
    return true;
}

int main(){
    int n;
    while (cin >> n, n != -1){
        if (n==0){cout << 0 << endl; continue;}
        LL ans = 0;
        for (int i=0; i<n; i++) ans += pow(3, gcd(i, n));
        if (n&1) ans += n*pow(3, n/2+1);
        else {ans += n/2*(pow(3, n/2)+pow(3,n/2+1));}
        assert(ans%(2*n)==0);
        cout << ans/(2*n) << endl;
    }
    return 0;
}
