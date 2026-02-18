#include <stdio.h>

double carre(double n){
    return n*n;
}

int main(void){
    double n;
    scanf("%lf",&n);
    printf("%.4lf\n",carre(n));

    return 0;
}
