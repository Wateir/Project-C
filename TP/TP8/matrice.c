#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

tMatrice MatAllouer(int NbLig, int NbCol){
    tMatrice tab=malloc(NbLig*sizeof(unsigned char*));
    if (tab == NULL) return NULL;

    for (int i =0;i<NbLig;i++){
        tab[i] = malloc(NbCol*sizeof(unsigned char));
        if (tab[i] == NULL) return NULL;
    }
    return tab;
}

tMatrice MatLire(int *pNbLig, int *pNbCol){
    printf("Combien de ligne et de colones ? : ");fflush(stdout);
    scanf("%d",pNbLig); scanf("%d",pNbCol);

    printf("Entrez les valeurs de la matrice :\n");
    tMatrice mat = MatAllouer(*pNbLig, *pNbCol);
    for (int i=0;i<*pNbLig;i++){
        for (int j=0;j<*pNbCol;j++){
            scanf("%hhu",&mat[i][j]);
        }
    }
    return mat;
}

void MatAfficher(tMatrice Mat, int NbLig, int NbCol){
    for (int i=0;i<NbLig;i++){
        for (int j=0;j<NbCol;j++){
            printf("%d ",Mat[i][j]);
        }
        printf("\n");
    }
}
tMatrice MatCopier(tMatrice Mat, int NbLig, int NbCol){
    tMatrice copie = MatAllouer(NbLig, NbCol);
    if (copie == NULL) return NULL;

    for (int i = 0; i < NbLig; i++) {
        for (int j = 0; j < NbCol; j++) {
            copie[i][j] = Mat[i][j];
        }
    }
    return copie;
}

void MatLiberer(tMatrice *pMat,int NbLig){
    if (*pMat == NULL) return;
    for (int i =0;i<NbLig;i++){
        free((*pMat)[i]);
    }
    free(*pMat);
    *pMat = NULL;
}
