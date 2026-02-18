#ifndef __MATRICE_H__
#define __MATRICE_H__

typedef unsigned char **tMatrice;

extern tMatrice MatAllouer(int NbLig, int NbCol);

extern tMatrice MatLire(int *pNbLig, int *pNbCol);

extern void MatAfficher(tMatrice Mat, int NbLig, int NbCol);

extern tMatrice MatCopier(tMatrice Mat, int NbLig, int NbCol);

extern void MatLiberer(tMatrice *pMat,int NbLig);

#endif
