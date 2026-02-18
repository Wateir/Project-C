#include <stdio.h>

#define MAX_LENGH 100

int main(void){
    double val[MAX_LENGH];
    int nbval;
    printf("Nombre de valeur ? ");
    scanf("%d",&nbval);
    printf("Ecrivez vos valeurs réels de la moyenne : "); fflush(stdout);
    double a,b;
    scanf("%lf",&a);

    double somme = a;
    for(int i=1;i<nbval && i< MAX_LENGH;i++){
        scanf("%lf",&b);
        val[i-1] = b;
        somme += b;
    }
    double moy = somme/nbval;
    printf("Val superieur a la moyenne ( %.2lf ) :",moy);
    for (int i=0;i<nbval && i< MAX_LENGH;i++){
        if (val[i]> moy){
            printf(" %.2lf",val[i]);
        }
    }
    printf("\n");

    return 0;
}
