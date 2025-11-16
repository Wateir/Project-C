#include <stdio.h>

int main(void){
    printf("Entrée un entier : "); fflush(stdout);
    int a;
    scanf("%d",&a);
    printf("%d\n",a*a);

    return 0;
}
