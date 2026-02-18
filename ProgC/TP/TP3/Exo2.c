#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#define MAX_LENGHT 9
#define EPSILON 1E-6

int main(void){
    int ordre;
    printf("Ordre de la matrice : ");
    scanf("%d",&ordre);

    double Matrice[MAX_LENGHT][MAX_LENGHT];

    for (int i=0;i<ordre;i++){
        printf("Ligne %d : ",i+1); fflush(stdout);
        scanf("%lf",&Matrice[i][0]);
        for (int j=1;j<ordre;j++){
            scanf("%lf",&Matrice[i][j]);
        }
    }

    int sym = 0;

    for(int i=0;i<ordre;i++){
        for(int j=0;j<ordre;j++){
            printf("%.2lf ",Matrice[i][j]);
            if (fabs(Matrice[i][j]-Matrice[j][i])>EPSILON){
                sym = 1;
            }
        }
        printf("\n");
    }

    if (sym==0) printf("Cette matrice est symetrique.\n");
    else printf("Cette matrice n'est pas symetrique.\n");

    return 0;
}
