#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <queue>
#include <set>
#include <climits>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()

vector<int> adj[3005];
set<pair<int, int> > forbid[3005];
int pre[3005][3005];
int dist[3005][3005];
bool visited[3005][3005];
int n, m, k;

void bfs(){
    queue<pair<int, int> > q;
    q.push(make_pair(1, 0));
    while (!q.empty()){
        int u = q.front().first, v = q.front().second; q.pop();
        for (vector<int>::iterator it = adj[u].begin();
          it != adj[u].end(); it++){
             if (forbid[v].find(make_pair(u, *it)) == forbid[v].end()){
                if (!visited[*it][u]){
                    visited[*it][u] = true;
                    pre[*it][u] = v;
                    dist[*it][u] = dist[u][v] + 1;
                    q.push(make_pair(*it, u));
                }
             }
        }
    }
}

void print_ans_rec(int u, int v){
    if (u != 1) print_ans_rec(v, pre[u][v]);
    printf("%d ", u);
}

int main(){
    scanf("%d%d%d", &n, &m, &k);
    while (m--){
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    while (k--){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        forbid[a].insert(make_pair(b, c));
    }
    for (int i=1; i<3004; i++) visited[1][i] = true;
    bfs();
    int ans = INT_MAX, p;
    for (int i=1; i<=n; i++){
        if (visited[n][i] && dist[n][i] < ans){
            ans = dist[n][i];
            p = i;
        }
    }
    if (ans != INT_MAX){
        printf("%d\n", ans);
        print_ans_rec(n, p);
        puts("");
    } else {
        puts("-1");
    }
    return 0;
}
