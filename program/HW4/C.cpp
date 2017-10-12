#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstring>
#include <stack>
#include <climits>
#include <cstdio>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
#define pb push_back
#define mt make_tuple
typedef long long LL;

struct Hungarian{
    int nx, ny;
    vector<int> mx, my;
    vector<vector<int> > e;
    vector<bool> mark;

    void init(int nx, int ny){
        this->nx = nx;
        this->ny = ny;
        mx.resize(nx); my.resize(ny);
        e.clear(); e.resize(nx);
        mark.resize(nx);
    }

    inline void add(int a, int b){
        e[a].push_back(b);
    }

    bool augment(int i){
        if (!mark[i]) {
            mark[i] = true;
            for (int j : e[i]){
                if (my[j] == -1 || augment(my[j])){
                    mx[i] = j; my[j] = i;
                    return true;
                }
            }
        }
        return false;
    }

    int match(){
        int ret = 0;
        fill(range(mx), -1);
        fill(range(my), -1);
        rep (i, nx){
            fill(range(mark), false);
            if (augment(i)) ret++;
        }
        return ret;
    }
} hun;

int n;
int mat[128][128];

int main(){
    while (cin >> n){
        hun.init(n+1, n+1);
        for (int i=1; i<=n; i++){
            for (int j=1; j<=n; j++){
                cin >> mat[i][j];
                if (mat[i][j]){
                    hun.add(i, j);
                }
            }
        }
        if (hun.match() != n){
            cout << -1 << endl;
        } else {
            int tab[128], inv[128], change[128];
            for (int i=1; i<=n; i++){
                tab[i] = hun.mx[i];
                inv[tab[i]] = i;
            }
            int cnt = 0;
            for (int i=1; i<=n; i++){
                change[i] = inv[i];
                if (i != inv[i]) cnt++;
                int tmp = tab[i];
                swap(tab[i], tab[inv[i]]);
                swap(inv[i], inv[tmp]);
            }
            cout << cnt << endl;
            for (int i=1; i<=n; i++){
                if (i!=change[i]){
                    cout << "R " << i << " " << change[i] << endl;
                }
            }
        }
    }
    return 0;
}
