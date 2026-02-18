#include <stdio.h>
#include <stdlib.h>

double *CreerTableau(int NbElts){
     double* tab = malloc(NbElts*sizeof(double));
     return tab;
}

void SaisirTableau(double *Tab, int NbElts){
    for (int i = 0;i<NbElts;i++){
        scanf("%lf",&Tab[i]);
    }
}
void AfficherTableau(double *Tab, int NbElts){
    for (int i=0;i<NbElts;i++){
        printf("%.3lf ",Tab[i]);
    }
    printf("\n");
}
void LibererTableau(double *Tab){
    free(Tab);
}

int main(void){
    int NbElts;
    printf("Nbelts ? : "); fflush(stdout);
    scanf("%d",&NbElts);
    double *tab = CreerTableau(NbElts);
    if (tab == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return 1;
    }
    printf("Entrée numero : ");fflush(stdout);
    SaisirTableau(tab,NbElts);
    AfficherTableau(tab,NbElts);
    LibererTableau(tab);
}
