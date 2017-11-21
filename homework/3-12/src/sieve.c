#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(void){
    bool* p;
    int n, i, j;
    scanf("%d", &n);
    p = malloc(n);
    memset(p, 0, n);
    p[0] = p[1] = 1;
    for (i=2; i*i<n; i++)
        if (!p[i])
            for (j=2*i; j<n; j+=i) p[j] = 1;
    for (i=0; i<n; i++)
        if (!p[i]) printf("%d\n", i);
    return 0;
}
