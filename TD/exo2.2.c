#include <stdio.h>

int main(void){
    char c;
    printf("Entrée un char : "); fflush(stdout);
    scanf("%c",&c);

    if ('A'<=c && c<='Z')
        printf("%c est une majuscule\n",c);
    else if ('a'<=c && c <='z')
        printf("%c est une minuscule\n",c);
    else if ('0'<=c && c <='9')
        printf("%c est un nombre\n",c);
    else
        printf("%c n'est pas une char lexicographique\n",c);


    return 0;
}
