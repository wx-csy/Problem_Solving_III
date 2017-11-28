#include <iostream>
using namespace std;

typedef long long LL;

void exgcd(LL a, LL b, LL &g, LL &x, LL &y){
    if (!b) g = a, x = 1, y = 0;
    else {
        exgcd(b, a % b, g, y, x),
        y -= x * (a / b);
    }
}

int main(){
    LL a, b, g, x, y, xp, yp;
    while (cin >> a >> b){
        exgcd(a, b, g, x, y);
        if (g != 1) {
            cout << "sorry" << endl;
        } else {
            xp = (x % b + b) % b;
            yp = y - (xp - x) / b * a;
            cout << xp << ' ' << yp << endl;
        }
    }

}
