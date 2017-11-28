#include <cstdio>
#include <cstring>
using namespace std;

int n, m, k;
int perm[256];
int result[256];
char str[256];
char strp[256];

void pow(int e){
    int b[256];
    int tmp[256];
    memcpy(b, perm, sizeof(b));
    for (int i=0; i<n; i++) result[i] = i;
    while (e){
        if (e&1) {
            for (int i=0; i<n; i++)
                tmp[i] = result[b[i]];
            memcpy(result, tmp, sizeof(tmp));
        }
        for (int i=0; i<n; i++){
            tmp[i] = b[b[i]];
        }
        memcpy(b, tmp, sizeof(b));
        e >>= 1;
    }
}

int main(){
    while (scanf("%d", &n), n){
        for (int i=0; i<n; i++) scanf("%d", perm+i), perm[i]--;
        while (scanf("%d", &k), k){
            getchar();
            gets(str);
            m = strlen(str);
            for (int i=m; i<n; i++) str[i] = ' ';
            str[n] = 0; strp[n] = 0;
            pow(k);
            for (int i=0; i<n; i++) strp[result[i]] = str[i];
            puts(strp);
        }
        puts("");
    }
    return 0;
}
