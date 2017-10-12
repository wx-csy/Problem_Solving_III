#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <cstring>
#include <climits>
#include <queue>
#include <numeric>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;

typedef pair<int, int> road;

vector<road> adj[105];

int disabled;
int dis[105];
bool visited[105];
int n, m;

int pre_value[105];
bool pre_used[108][3005];

bool pre_dfs(){
    memset(pre_used, 0, sizeof(pre_used));
    for (int src = 1; src <= n; src++){
        queue<pair<int, int> > q;
        Rep (i, n) visited[i] = false;
        visited[src] = true; dis[src] = 0;
        q.push(make_pair(src, 0));
        while (!q.empty()){
            int u = q.front().first, dist = q.front().second + 1;
            q.pop();
            for (vector<road>::iterator it = adj[u].begin(); it != adj[u].end(); it++){
                if (!visited[it->first]){
                    pre_used[src][it->second] = true;
                    visited[it->first] = true;
                    dis[it->first] = dist;
                    q.push(make_pair(it->first, dist));
                }
            }
        }
        Rep (i, n) if (!visited[i]) return false;
        pre_value[src] = accumulate(dis + 1, dis + 1 + n, 0);
    }
    return true;
}

bool dfs(int src, int& ans){
    if (!pre_used[src][disabled]) {
        ans += pre_value[src];
        return true;
    }
    queue<pair<int, int> > q;
    Rep (i, n) visited[i] = false;
    visited[src] = true; dis[src] = 0;
    q.push(make_pair(src, 0));
    while (!q.empty()){
        int u = q.front().first, dist = q.front().second + 1;
        q.pop();
        for (vector<road>::iterator it = adj[u].begin(); it != adj[u].end(); it++){
            if (it->second != disabled && !visited[it->first]){
                visited[it->first] = true;
                dis[it->first] = dist;
                q.push(make_pair(it->first, dist));
            }
        }
    }
    Rep (i, n) if (!visited[i]) return false;
    ans += accumulate(dis + 1, dis + n + 1, 0);
    return true;
}

void calc(){
    int ans = 0;
    Rep (i, n)
        if (!dfs(i, ans)){
            puts("INF");
            return;
        }
    printf("%d\n", ans);
}

int main(){
    while (~scanf("%d%d", &n, &m)){
        int u, v;
        Rep (i, n) adj[i].clear();
        Rep (i, m){
            scanf("%d%d", &u, &v);
            adj[u].push_back(make_pair(v, i));
            adj[v].push_back(make_pair(u, i));
        }
        if (!pre_dfs())
            Rep (i, m) puts("INF");
        else {
            for (disabled = 1; disabled <= m; disabled++)
                calc();
        }
    }
    return 0;
}

