#include <stdio.h>

int main(void){
    printf("Entrée une année : "); fflush(stdout);
    int annee;
    scanf("%d",&annee);

    if (annee%4==0){
        if (annee%100==0){
            if(annee%400==0){
                printf("Année Bissextile\n");
                return 0;
            }
            else{
                printf("Pas une année bissextile\n");
                return 0;
            }
        }
        else{
            printf("Année Bissextile\n");
            return 0;
        }
    }
    else{
        printf("Pas une année bissextile\n");
        return 0;
    }

    return 0;
}
