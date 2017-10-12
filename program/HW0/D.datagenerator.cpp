#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
#define pb push_back
#define mt make_tuple
typedef long long LL;

const int n = 1000;

int main(){
    ios::sync_with_stdio(false);    cin.tie(0);
    freopen("d.txt", "w", stdout);
    srand(time(NULL));
    cout << n << endl;
    for (int i=0; i<n; i++){
        cout << rand() << ' ' << rand() << ' ' << rand() * 5000 + rand() << endl;
    }
    cout << 0 << endl;
    return 0;
}
