#include "ti.h"
#include "image.h"
#include <math.h>
#include <stdlib.h>

tImage Rotation(tImage Im){
    tImage NouvelleIm = ImAllouer(ImNbCol(Im),ImNbLig(Im));
    if (NouvelleIm == NULL) return NULL;

    for(int i=0;i<ImNbLig(Im);i++){
        for(int j=0;j<ImNbCol(Im);j++){
            NouvelleIm->NivGris[j][i] = Im->NivGris[i][j];
        }
    }
    return Im;
}

tImage AppliquerTable(unsigned char Table[GRIS_MAX], tImage Im){
    tImage NouvelleIm = ImAllouer(ImNbLig(Im),ImNbCol(Im));
    if (NouvelleIm == NULL) return NULL;

    for(int i=0;i<ImNbLig(Im);i++){
        for(int j=0;j<ImNbCol(Im);j++){
            NouvelleIm->NivGris[i][j] = Table[Im->NivGris[i][j]];
        }
    }
    return Im;
}

void RemplirTableInversion(unsigned char Table[GRIS_MAX]){
    for (int i= 0;i<GRIS_MAX;i++){
        Table[i] = GRIS_MAX-i;
    }
}

void RemplirTableGamma(double Gamma, unsigned char Table[256]){
    for (int i= 0;i<GRIS_MAX;i++){
        Table[i] = round(255*pow(i/255,Gamma));
    }
}
