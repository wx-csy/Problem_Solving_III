#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

const int n = 100;
int main(){
    srand(time(NULL));
    freopen("test.txt", "w", stdout);
    cout << n << endl;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (i==j) cout << 0 << ' '; else cout << rand() << ' ';
        }
        cout << endl;
    }
    return 0;
}
