#include <stdio.h>

int main(void){
    printf("Entrez une tempererature en Farenheit : "); fflush(stdout);
    int Far;
    scanf("%d",&Far);
    int cel = (5*(Far-32))/9;
    printf("Result en Celcius = %d\n",cel);

    return 0;
}
