#include <iostream>
using namespace std;

int n;
int d[200][200];
int d2[200][200];

int main(){
    cin >> n;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cin >> d2[i][j];
    for (int k=0; k<n; k++){
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                d[i][j] = d2[i][j];
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                d2[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        for (int i=0; i<n; i++){
            for (int j=0; j<n; j++){
                cout << d2[i][j] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
