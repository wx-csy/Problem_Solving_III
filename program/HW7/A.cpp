#include <cstdio>
#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long LL;

#define int LL
const int MAXX = 100000;
bool p[MAXX];

void sieve(){
    p[0] = p[1] = 1;
    for (int i = 2; i*i < MAXX; i++) if (!p[i])
        for (int j = i*i; j < MAXX; j+=i) p[j] = true;
}

vector<LL> primes;
bool isnp[1000005];
int l, r;

#undef int
int main(){
#define int LL
    sieve();
    for (int i=0; i < MAXX; i++) if (!p[i]) primes.push_back(i);
    while (cin >> l >> r){
        memset(isnp, 0, r-l+1);

        for (int i=0; (LL)(primes[i]) * primes[i] <= (LL)r ; i++){
            // cout << __func__ << endl;
            for (LL x = (l % primes[i])?(l + primes[i] - l % primes[i]):l; x <= r; x += primes[i]){
                if (x != primes[i]) isnp[x - l] = 1;
            }
        }

        vector<LL> ps;
        for (LL x = 0; x <= r-l; x++) if (x + l>=2 && !isnp[x]) ps.push_back(x+l);
        if (ps.size()<2) {
            cout << "There are no adjacent primes." << endl;
            continue;
        }

        int dis1 = INT_MAX, dis2 = 0;
        int id1, id2;
        for (int i=1; i < ps.size(); i++){
            int dis = ps[i] - ps[i-1];
            if (dis < dis1) dis1 = dis, id1 = i;
            if (dis > dis2) dis2 = dis, id2 = i;
        }
        cout << ps[id1-1] << ',' << ps[id1] << " are closest, "
             << ps[id2-1] << ',' << ps[id2] << " are most distant." << endl;
    }
    return 0;
}
