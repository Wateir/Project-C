#include "image.h"
#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TAMPON_TAILLE 256

#define MAX_NIV_GRIS 255.0 //le .0 assure que c'est une divistion de réel
#define TRANSFORMATION_INTERVALL(val, M) ((int)round(MAX_NIV_GRIS * (val) / (M)))

tImage ImAllouer(int NbLignes, int NbColonnes){
    tImage Im = malloc(sizeof(struct sImage));
    if (Im == NULL) return NULL;

    Im->NivGris = MatAllouer(NbLignes, NbColonnes);
    if (Im->NivGris == NULL) return NULL;
    Im->NbCol = NbColonnes;
    Im->NbLig = NbLignes;
    return Im;
}

void ImLiberer(tImage *pIm){
    MatLiberer(&((*pIm)->NivGris),(*pIm)->NbLig);
    free(*pIm);
    *pIm = NULL;
}

int ImNbLig(tImage Im){
    return Im->NbLig;
}

int ImNbCol(tImage Im){
    return Im->NbCol;
}

tMatrice ImNivGris(tImage Im){
    return Im->NivGris;
}

// Remplacement de la fonction par une macro
//static int transformationIntervall(int val, int M){
//    return round(255.0*val/M);
//}
#define PASSER_COMMENTAIRE while (Tampon[0] == '#') fgets(Tampon, sizeof(Tampon), fichier)
#define ACTUALISER_TAMPON fgets(Tampon, sizeof(Tampon), fichier)

tImage ImLireTexte(FILE* fichier,int NbLig,int NbCol, int M){
    tImage Im = ImAllouer(NbLig, NbCol);
    if (Im == NULL) {
        #ifdef DEBUG
            printf("Im, Allocation loupé\n");
        #endif
        return NULL;
    }
    int temp,val;
    for (int k = 0; k < NbLig; k++) {
        for (int j = 0; j < NbCol; j++) {
            val = fscanf(fichier,"%d",&temp);
            if (val != 1) {
                ImLiberer(&Im);
                #ifdef DEBUG
                    printf("fgetc a loupé, pour le char position [%d][%d]\n",k,j);
                #endif
                ImLiberer(&Im);
                return NULL;
            }
            if (temp != ' ' && temp != '\n' && temp != '\t'){
                Im->NivGris[k][j] = (unsigned char) TRANSFORMATION_INTERVALL(temp, M);
                // (typeof(*Im->NivGris[k])) utilisation de ce cast, si la definition de tMatrice change, cela restera correct
            }
        }
    }
    return Im;
}

tImage ImLireBinaire(FILE* fichier,int NbLig,int NbCol,long position){
    tImage Im = ImAllouer(NbLig, NbCol);
    if (Im == NULL) {
        #ifdef DEBUG
            printf("Im, Allocation loupé\n");
        #endif
        return NULL;
    }
    fseek(fichier,position,SEEK_SET);
    for(int i=0;i<NbLig; i++){
        fread(Im->NivGris[i],sizeof(unsigned char),ImNbCol(Im),fichier);
    }
    return Im;
}

tImage ImLire(char NomFichier[]){
    FILE* fichier = fopen(NomFichier, "rt");
    char Tampon[TAMPON_TAILLE];

    ACTUALISER_TAMPON;
    PASSER_COMMENTAIRE;
    if(Tampon[0]!='P'){
        #ifdef DEBUG
            printf("%c != P, Non PGM fichier, quitte\n",Tampon[0]);
        #endif
        return NULL;
    }
    char type = Tampon[0];
    if (type != '2' || type !='5'){
        #ifdef DEBUG
            printf("%d != 2 ou !=5, PGM non reconnu, quitte\n",Tampon[1]);
        #endif
        return NULL;
    }
    int NbLig, NbCol;
    PASSER_COMMENTAIRE;
    ACTUALISER_TAMPON;
    if (sscanf(Tampon, "%d %d", &NbCol, &NbLig) != 2){
        #ifdef DEBUG
            printf("NbLig ou/et NbCol non lu\n Tampon = [%s]\n",Tampon);
        #endif
        return NULL;
    }
    #ifdef DEBUG
        printf("ImLire : NbLig = %d NbCol = %d\n",NbLig,NbCol);
    #endif
    int M;
    PASSER_COMMENTAIRE;
    ACTUALISER_TAMPON;
    if (sscanf(Tampon, "%d", &M) != 1) {
        #ifdef DEBUG
            printf("M non lu\nTampon = [%s]\n",Tampon);
        #endif
        return NULL;
    }
    tImage Im;
    if(type=='5'){
        fclose(fichier);
        fichier = fopen(NomFichier,"rb");
        long position;
        position=ftell(fichier);
        Im = ImLireBinaire(fichier,NbLig,NbCol,position);
    }
    else{
        Im = ImLireTexte(fichier,NbLig,NbCol,M);
    }
    if (Im == NULL){
        #ifdef DEBUG
            printf("Lecture à loupé");
        #endif
    }
    fclose(fichier);
    return Im;

}

#undef ACTUALISER_TAMPON
#undef PASSER_COMMENTAIRE

void ImEcrire(tImage Im, char NomFichier[]){
     FILE* fichier = fopen(NomFichier, "w");

    fprintf(fichier, "P2\n");
    fprintf(fichier, "%d %d\n", Im->NbCol, Im->NbLig);
    fprintf(fichier, "255\n");

    #ifdef DEBUG
        printf("NbCol = %d, NbLig = %d\n", Im->NbLig, Im->NbCol);
    #endif

    for (int k=0;k<Im->NbLig;k++){
        for (int j=0;j<Im->NbCol;j++){
            fprintf(fichier, "%d ",Im->NivGris[k][j]);
            #ifdef DEBUG
                //printf("%3hhu ",Im->NivGris[k][j]);
            #endif
        }
        #ifdef DEBUG
            //printf("\n");
        #endif
        fprintf(fichier, "\n");
    }
    fclose(fichier);

}
