#include <stdio.h>

int main(void){
    printf("Entrée un entier : "); fflush(stdout);
    unsigned char a;
    scanf("%hhu",&a);
    unsigned char res = a*a;
    printf("%d\n",res);

    return 0;
}
