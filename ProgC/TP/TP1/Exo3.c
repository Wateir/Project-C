#include <stdio.h>
#include <math.h>

int main(void){
    printf("Entrée un réel : "); fflush(stdout);
    double a;
    scanf("%lf",&a);
    printf("%lf\n",sqrt(a));

    return 0;
}
