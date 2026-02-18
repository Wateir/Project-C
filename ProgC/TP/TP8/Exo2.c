#include "matrice.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>

void testMatriceH(void){
    int NbCol,NbLig;
    tMatrice mat = MatLire(&NbCol,&NbLig);
    printf("Affichage Mat\n");
    MatAfficher(mat,NbLig,NbCol);
    tMatrice mat2 = MatCopier(mat,NbLig,NbCol);
    printf("Affichage Mat2\n");
    MatAfficher(mat2,NbLig,NbCol);
    MatLiberer(&mat,NbLig);
    MatLiberer(&mat2, NbLig);
}

int testImageH(void){
    // Test allocation and free of a small image
    tImage Im = ImAllouer(4, 4);
    printf("NbLig = %d\n", ImNbLig(Im));
    printf("NbCol = %d\n", ImNbCol(Im));
    int NbLig = ImNbLig(Im);
    ImLiberer(&Im, NbLig);


    char *fichier = "dragon.pgm";
    tImage feep = ImLire(fichier);
    if (feep == NULL){
        #ifdef DEBUG
            printf("ImLire a loupé\n");
        #endif
        return 1;
    }

    #define RETOURNER

    #ifdef RETOURNER
    tImage feep2 = ImAllouer(ImNbCol(feep),ImNbLig(feep));

    for(int i=0;i<ImNbLig(feep);i++){
        for(int j=0;j<ImNbCol(feep);j++){
           feep2->NivGris[j][i] = feep->NivGris[i][j];
        }
    }
    #else
    tImage feep2 = ImAllouer(ImNbLig(feep),ImNbCol(feep));

    feep2->NivGris = MatCopier(feep->NivGris,ImNbLig(feep),ImNbCol(feep));
    #endif
    char *fich = "feep2.pgm";
    ImEcrire(feep2, fich);


    NbLig = ImNbLig(feep);
    int NbLig2 = ImNbLig(feep2);
    ImLiberer(&feep2, NbLig2);
    ImLiberer(&feep, NbLig);
    return 0;
}


int main(void){
    int val = 0;
    // testMatriceH();
    val = testImageH();
    return val;
}
