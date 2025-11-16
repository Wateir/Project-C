#include <stdio.h>
#define NBR 5

int main(void){
    printf("Ecrivez %d réels : ",NBR); fflush(stdout);
    double a,b;
    scanf("%lf",&a);

    double max =a;
    for(int i=1;i<NBR;i++){
        scanf("%lf",&b);
        if (max<b) max=b;
    }

    printf("%.2f\n",max);

    return 0;
}
