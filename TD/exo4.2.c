#include <stdio.h>

int Tri2(int a, int b, int *max, int *min){
    if (a > b) {
        *max = a;
        *min = b;
    }
    else{
        *max = b;
        *min = a;
    }

    return 0;
}

int main(void){
    int a;
    int b;
    int min;
    int max;

    scanf("%d",&a);
    scanf("%d",&b);

    Tri2(a,b,&max,&min);

    printf("%d < %d\n",min,max);

    return 0;
}
