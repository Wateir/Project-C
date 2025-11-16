#include <limits.h>
#include <stdio.h>
#define MAX_LENGHT 80

int main(void){
    char texte[MAX_LENGHT+1];

    scanf("%c",&texte[0]);
    int i=0;
    while (texte[i]!='\n' && i < MAX_LENGHT) {
        i++;
        scanf("%c",&texte[i]);
    }
    texte[++i]='\0';
    int nbchar = i;
    for (i=0;i<nbchar;i++){
        printf("%c",texte[i]);
    }
    printf("\n");
    for (i=nbchar-1;i>=0;i--){
        printf("%c",texte[i]);
    }
    printf("\n");
    printf("Nb char = %d\n",nbchar-1);


    int EstPalindrome = 1;
    for (int j= 0,k = i-2; j < k / 2;) {
        while (texte[j] == ' ') j++;
        while (texte[k] == ' ') k--;
        if (texte[j] != texte[k]) {
            EstPalindrome = 0;
        }
        j++;
        k--;
    }

    if (EstPalindrome) {
        printf("C'est un palindrome\n");
    } else {
        printf("Pas un palindrome\n");
    }

    return 0;
}
