#include <iostream>
using namespace std;

int n;
int d[200][200];

int main(){
    cin >> n;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cin >> d[i][j];
    for (int k=0; k<n; k++){
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                cout << d[i][j] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
