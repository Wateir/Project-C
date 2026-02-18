#include <stdio.h>

int main(void){
    printf("Combien de ligne ? ");fflush(stdout);
    int nbr_ligne;
    scanf("%d",&nbr_ligne);

    for (int i=0;i<nbr_ligne;i++){
        for (int j=0;j<nbr_ligne-i;j++){
            printf(" ");fflush(stdout);
        }
        for (int j=0;j<i*2+1;j++){
            printf("%s","*");fflush(stdout);
        }
        printf("\n");
    }
}
