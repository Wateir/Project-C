#include "matrice.h"
#include <stdio.h>

int main(void){
    int NbCol,NbLig;
    tMatrice mat = MatLire(&NbCol,&NbLig);
    printf("Affichage Mat\n");
    MatAfficher(mat,NbLig,NbCol);
    tMatrice mat2 = MatCopier(mat,NbLig,NbCol);
    printf("Affichage Mat2\n");
    MatAfficher(mat2,NbLig,NbCol);
    MatLiberer(&mat,NbLig);
    MatLiberer(&mat2, NbLig);
    return 0;
}
