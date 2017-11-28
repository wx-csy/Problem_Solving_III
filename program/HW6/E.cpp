#include <iostream>
#include <string>
using namespace std;

const int p = 9973;

int inv(int x){
    int e = p - 2;
    int r = 1;
    while (e){
        if (e & 1) r = r * x % p;
        x = x * x % p;
        e >>= 1;
    }
    return r;
}

string str;
int pref[100005];
int main(){
    int k;
    pref[0] = 1;
    while (cin >> k){
        cin >> str;
        for (int i=0; i<str.size(); i++){
            pref[i+1] = str[i] - 28;
        }
        for (int i=1; i<=str.size(); i++){
            pref[i] = pref[i] * pref[i-1] % p;
        }
        for (int i=0; i<k; i++){
            int a, b;
            cin >> a >> b;
            cout << (pref[b] * inv(pref[a-1])) % p << endl;
        }
    }

    return 0;
}
