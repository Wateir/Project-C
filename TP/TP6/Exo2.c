#include <stdio.h>
#include <stdlib.h>

typedef unsigned char **tMatrice;

tMatrice MatAllouer(int NbLig, int NbCol){
    tMatrice tab=malloc(NbLig*sizeof(unsigned char*));
    if (tab == NULL) return NULL;

    unsigned char* elt = malloc(NbLig*NbCol*sizeof(unsigned char));
    if (elt == NULL) {
        free(tab);
        return NULL;
    }

    for (int i = 0;i<NbLig;i++){
        tab[i] = &elt[i*NbCol];
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

void MatLiberer(tMatrice *pMat){
    if (*pMat == NULL) return;
    free(*pMat[0]);
    free(*pMat);
    *pMat = NULL;
}

int main(void){
    int NbCol,NbLig;
    tMatrice mat = MatLire(&NbCol,&NbLig);
    printf("Affichage Mat\n");
    MatAfficher(mat,NbLig,NbCol);
    tMatrice mat2 = MatCopier(mat,NbLig,NbCol);
    printf("Affichage Mat2\n");
    MatAfficher(mat2,NbLig,NbCol);
    MatLiberer(&mat);
    MatLiberer(&mat2);
    return 0;
}
