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
        for (int i=nx-1; i>=0; i--){
            fill(range(mark), false);
            if (augment(i)) ret++;
        }
        return ret;
    }
} hun;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        int n; scanf("%d", &n);
        hun.init(n, 100005);
        rep (i, n){
            int xi, yi; scanf("%d%d", &xi, &yi);
            for (int j=xi; j<=yi; j++){
                hun.add(i, j);
            }

        }
        hun.match();
        vector<int> v;
        for (int i=0; i<n; i++){
            if (hun.mx[i] != -1) v.push_back(i+1);
        }
        printf("%d\n", v.size());
        for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
            printf("%d", *it);
            if (it+1 != v.end()) printf(" "); else puts("");
        }
    }
    return 0;
}
