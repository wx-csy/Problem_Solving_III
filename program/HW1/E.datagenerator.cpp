#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int n = 16;
const int k = 10;
const int mod = 500;

int main(int argc, char* argv[]){
    ios::sync_with_stdio(false);    cin.tie(0);
    freopen("e.txt", "w", stdout);
    srand(atoi(argv[1]) + time(NULL));
    cout << n << ' ' << k << endl;
    for (int i=0; i<n; i++){
        cout << (rand() % mod + 1) << ' ' << (rand() % mod + 1) << endl;
    }
    cout << 0 << endl;
    return 0;
}
