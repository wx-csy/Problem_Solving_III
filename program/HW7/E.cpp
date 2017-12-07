#include <iostream>
using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define Rep(i, n) for (int i = 1; i <= (n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;

int dp[305][305];
int cnt[305][305];

int gcd(int a, int b){return a?gcd(b%a, a):b;}

int main(){
    Rep(i, 300) Rep(j, 300) dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + (gcd(i, j) == 1);
    Rep(i, 300) Rep(j, 300) cnt[i][j] = cnt[i-1][j] + cnt[i][j-1] - cnt[i-1][j-1] + dp[i][j] - dp[i/2][j/2];
    int x, y;
    while (cin >> x >> y, x) cout << cnt[x-1][y-1]*2 << endl;
    return 0;
}
