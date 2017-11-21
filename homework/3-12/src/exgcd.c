#include <stdio.h>

void exgcd(int a, int b, int*g, int*x, int*y){
    if (!b) *g = a, *x = 1, *y = 0;
    else exgcd(b, a % b, g, y, x),
         *y -= *x * (a / b);
}

int main(void){
    int a, b, g, x, y;
    scanf("%d%d", &a, &b);
    exgcd(a, b, &g, &x, &y);
    printf("gcd(%d, %d) = %d = %d*%d + %d*%d", a, b, g, x, a, y, b);
    return 0;
}
