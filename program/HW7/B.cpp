#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>
using namespace std;


typedef long long LL;

const int MAXX = 3e6+5;
LL phi[MAXX];
int prime[MAXX/4], sz;

void sieve(){
    phi[1] = 1;
    for (int i = 2; i < MAXX; i++){
        if (!phi[i]) phi[i] = i-1, prime[sz++] = i;
        for (int j=0; j<sz && i*prime[j] < MAXX; j++){
            if (i%prime[j] == 0){
                phi[i*prime[j]] = phi[i]*prime[j];
                break;
            }
            phi[i*prime[j]] = phi[i]*(prime[j]-1);
        }
    }
}

int main(){
    sieve();
    partial_sum(phi, phi+MAXX, phi);
    int i, j;
    while (cin >> i >> j){
        cout << phi[j]-phi[i-1] << endl;
    }
    return 0;
}
