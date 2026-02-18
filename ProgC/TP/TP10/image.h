#ifndef __IMAGE_H__
#define __IMAGE_H__
#include "matrice.h"

typedef struct sImage *tImage;

struct sImage
{
    int NbLig ; // Nombre de lignes de l’image
    int NbCol ; // Nombre de colonnes de l’image
    tMatrice NivGris ; // Matrice des niveaux de gris de l’image
};

extern tImage ImAllouer(int NbLignes, int NbColonnes);

extern void ImLiberer(tImage *pIm);

extern int ImNbLig(tImage Im);

extern int ImNbCol(tImage Im);

extern tMatrice ImNivGris(tImage Im);

extern tImage ImLire(char NomFichier[]);

extern void ImEcrire(tImage Im, char NomFichier[]);

#endif
