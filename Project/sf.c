#include "inode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sf.h"

#define TAILLE_TAMPON 640

//Crée et retourne un super-bloc associé au SF de nom nomDisque
static tSuperBloc CreerSuperBloc(char nomDisque[]){
    tSuperBloc bloc = malloc(sizeof(struct sSuperBloc));
    if (bloc == NULL){
        fprintf(stderr," CreerSuperBloc : probleme creation");
        return NULL;
    }
    strcpy(bloc->nomDisque, nomDisque);
    bloc->dateDerModif = time(NULL);
    return bloc;
}

//affiche les informations contenues dans le super-bloc passé en paramètre
static void AfficherSuperBloc(tSuperBloc superBloc){
    printf("taille bloc = %d, date der modif = %s\n",TAILLE_BLOC,ctime(&(superBloc)->dateDerModif));
}

//Détruit le super-bloc référencé par le paramètre pSuperBloc
static void DetruireSuperBloc(tSuperBloc *pSuperBloc){
    free(*pSuperBloc);
    *pSuperBloc = NULL;
}

tSF CreerSF(char nomDisque[]){
    tSF sf = malloc(sizeof(struct sSF));
    sf->superBloc = CreerSuperBloc(nomDisque);
    sf->listeInodes.nbInodes = 0;
    sf->listeInodes.dernier = NULL;
    sf->listeInodes.premier = NULL;
    return sf;
}

void AfficherSF(tSF sf){
    if (sf ==NULL){
        #ifdef debug
        fprintf(stderr,"AfficherSF : le systeme de fichier n'existe pas");
        #endif
        return;
    }
    printf("sf de nom %s, super bloc :\n",sf->superBloc->nomDisque);
    AfficherSuperBloc(sf->superBloc);
    if (sf->listeInodes.nbInodes!=0){
        printf("Inodes :\n");
        struct sListeInodesElement* temp = sf->listeInodes.premier;
        for (int i = 0;i<sf->listeInodes.nbInodes;i++){
            AfficherInode(temp->inode);
            temp = temp->suivant;
        }
    }
    sf->superBloc->dateDerModif = time(NULL);
}

void DetruireSF(tSF *pSF){
    DetruireSuperBloc(&((*pSF)->superBloc));
    free(*pSF);
    *pSF = NULL;
}

static struct sListeInodesElement* CreerListeInodesElement(tInode inode){
    if(inode == NULL){
        #ifdef debug
        fprintf(stderr,"CreerListeInodesElement : l'inode n'existe pas");
        #endif
        return NULL;
    }
    struct sListeInodesElement* liste = malloc(sizeof(struct sListeInodesElement));
    if(liste == NULL){
        #ifdef debug
        fprintf(stderr,"CreerListeInodesElement : l'allocation à loupé");
        #endif
        return NULL;
    }
    liste->inode = inode;
    liste->suivant = NULL;
    return liste;
}

long Ecrire1BlocFichierSF(tSF sf, char nomFichier[], natureFichier type){
    if(sf == NULL){
        #ifdef debug
        fprintf(stderr,"AfficherSF : le systeme de fichier n'existe pas");
        #endif
        return -1;
    }
    if(sf->listeInodes.nbInodes==0){
        tInode inode = CreerInode(0, type);
        if(inode == NULL){
            #ifdef debug
            fprintf(stderr,"Ecrire1BlocFichierSF : l'allocation de l'inode à loupé");
            #endif
            return -1;
        }
        sf->listeInodes.premier = CreerListeInodesElement(inode);
        sf->listeInodes.dernier = sf->listeInodes.premier;
        sf->listeInodes.nbInodes = 1;
    }
    sf->listeInodes.premier->inode->type = type;

    unsigned char* tampon = malloc(sizeof(unsigned char)*TAILLE_TAMPON);

    FILE *fichier = fopen(nomFichier, "r");

    int NombreCaraLu=0;
    int caractere;
    while ((caractere = fgetc(fichier))!=EOF && NombreCaraLu<TAILLE_TAMPON){
        tampon[NombreCaraLu] = caractere;
    }
    sf->superBloc->dateDerModif = time(NULL);
    return EcrireDonneesInode1bloc(sf->listeInodes.premier->inode, tampon,NombreCaraLu);

}
