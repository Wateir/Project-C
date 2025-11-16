#include <stdio.h>

int main(void){
    int a,b;
    printf("Ecrivez deux entier : "); fflush(stdout);
    scanf("%d",&a);
    scanf("%d",&b);
    printf("a = %d, b = %d\n",a,b);
    int c;
    c = a;
    a = b;
    b = c;
    printf("a = %d, b = %d\n",a,b);

    return 0;
}
