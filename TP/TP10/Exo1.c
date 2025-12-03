#include "image.h"
#include <stdio.h>

int main(void){
    char *fichier = "dragon.pgm";
    tImage feep = ImLire(fichier);
    if (feep == NULL){
        #ifdef DEBUG
            printf("ImLire a loupé\n");
        #endif
        return 1;
    }
    tImage feep2 = ImAllouer(ImNbLig(feep),ImNbCol(feep));
    MatLiberer(&feep2->NivGris ,feep2->NbLig);
    feep2->NivGris = MatCopier(feep->NivGris,ImNbLig(feep),ImNbCol(feep));
    char *fich = "feep2.pgm";

    #ifdef DEBUG
        printf("dragon : NbCol = %d, NbLig = %d\n", feep->NbLig, feep->NbCol);
        printf("feep2 : NbCol = %d, NbLig = %d\n", feep2->NbLig, feep2->NbCol);
    #endif

    ImEcrire(feep2, fich);
    ImLiberer(&feep2);
    ImLiberer(&feep);
    return 0;
}
