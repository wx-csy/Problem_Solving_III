#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

typedef long long LL;
LL pow(LL a, LL b){LL r=1; while(b){if(b&1)r*=a;a*=a;b>>=1;}; return r;}
LL gcd(LL a, LL b){return a?gcd(b%a, a):b;}

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
