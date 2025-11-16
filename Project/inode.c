#include <stdio.h>
#include <stdlib.h>
#ifdef DEBUG
#include <string.h>
#endif
#include <time.h>
#include "inode.h"

#ifdef DEBUG
#define TEST_EXISTANCE(pointeur,NomFonction,MessageErreur) \
    if ((pointeur) == NULL) { \
        fprintf(stderr, "%s : %s\n", NomFonction, MessageErreur); \
    }
#else
#define TEST_EXISTANCE(pointeur,NomFonction,MessageErreur)
#endif

#define STRING_ENUM (12+1)

tBloc CreerBloc(void){
    tBloc bloc = malloc(TAILLE_BLOC);
    if (bloc == NULL){
        fprintf(stderr," CreerBloc : probleme creation");
        return NULL;
    }
    return bloc;
}

void DetruireBloc(tBloc *pBloc){
    free(*pBloc);
    *pBloc = NULL;
}

long EcrireContenuBloc(tBloc bloc, unsigned char *contenu, long taille){
    TEST_EXISTANCE(bloc,"EcrireContenuBloc","le bloc n'existe pas")
    int i;
    for (i=0;i<taille && i<TAILLE_BLOC;i++){
        bloc[i] = contenu[i];
    }
    return (long) i;
}

long LireContenuBloc(tBloc bloc, unsigned char *contenu, long taille){
    TEST_EXISTANCE(bloc,"LireContenuBloc","le bloc n'existe pas")
    int i;
    for (i=0;i<taille||i<TAILLE_BLOC;i++){
        contenu[i] = bloc[i];
    }
    return (long) i;
}

tInode CreerInode(unsigned int numInode, natureFichier type){
    tInode inode= malloc(sizeof(struct sInode));
    if (inode == NULL){
        fprintf(stderr," CreerInode : probleme creation");
        return NULL;
    }
    inode->blocDonnees[0]= NULL; // on initialise a NULL pour etre sur que si c'est pas changer, Detruire vera la non initialisation
    inode->numero = numInode;
    inode->type = type;
    inode->dateDerModifInode = time(NULL);

    return inode;
}

void DetruireInode(tInode* pInode){
    if ((*pInode)->blocDonnees[0] != NULL){
        free((*pInode)->blocDonnees[0]);
    }
    free(*pInode);
    *pInode = NULL;
}

unsigned int Numero(tInode inode){
    TEST_EXISTANCE(inode,"Numero","l'inode n'existe pas")
    inode->dateDerAcces = time(NULL);
    return inode->numero;
}

time_t DateDerAcces(tInode inode){
    TEST_EXISTANCE(inode,"DateDerAcces","l'inode n'existe pas")
    inode->dateDerAcces = time(NULL);
    return inode->dateDerAcces;
}

time_t DateDerModif(tInode inode){
    TEST_EXISTANCE(inode,"DateDerModif","l'inode n'existe pas")
    inode->dateDerAcces = time(NULL);
    return inode->dateDerModif;
}

time_t DateDerModifFichier(tInode inode){
    TEST_EXISTANCE(inode,"DateDerModifFichier","l'inode n'existe pas")
    inode->dateDerAcces = time(NULL);
    return inode->dateDerModifInode;
}

natureFichier Type(tInode inode){
    TEST_EXISTANCE(inode,"Type","l'inode n'existe pas")
    inode->dateDerAcces = time(NULL);
    return inode->type;
}


long Taille(tInode inode){
    TEST_EXISTANCE(inode,"Taille","l'inode n'existe pas")
    inode->dateDerAcces = time(NULL);
    return inode->taille;
}

//Retourne le bloc à l'inode (inode)
static unsigned char** BlocDonnees(const tInode inode){
    TEST_EXISTANCE(inode,"BlocDonnees","l'inode n'existe pas")
    inode->dateDerAcces = time(NULL);
    return inode->blocDonnees;
}

//Retourne le string associé au type (type)
static const char* stringNatureFichier(const natureFichier type){
    if(type == 0) return "ORDINAIRE";
    if(type == 1) return "REPERTOIRE";
    return "AUTRE";
}

void AfficherInode(tInode inode){
    TEST_EXISTANCE(inode,"AfficherInode","l'inode n'existe pas")
    if (inode->blocDonnees[0]==NULL){
        #ifdef DEBUG
        fprintf(stderr,"AfficherInode : inode->blocDonnees[0] est vide\n");
        #endif
        return;
    }
    inode->dateDerAcces = time(NULL);
    printf("-----Inode-----[%d]\n",Numero(inode));
    printf("type : %s\n",stringNatureFichier(Type(inode)));
    printf("\ttaille : %ld octets\n",Taille(inode));

    time_t date = DateDerAcces(inode);
    printf("\tdate dernier accès : %s",ctime(&date));
    date = DateDerModif(inode);
    printf("\tdate derniere modification : %s",ctime(&date));
    date = DateDerModifFichier(inode);
    printf("\tdate dernier modification inode : %s",ctime(&date));

    printf("\tDonnées :\n");
    printf("%s\n",*BlocDonnees(inode));
}

long EcrireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille){
    if (inode == NULL || contenu == NULL || taille < 0) {
        #ifdef DEBUG
        fprintf(stderr,"EcrireDonneesInode1bloc : paramètres invalides\n");
        #endif
        return -1;
    }
    inode->blocDonnees[0] = CreerBloc();
    if (inode->blocDonnees[0]==NULL){
        #ifdef DEBUG
        fprintf(stderr,"EcrireDonneesInode1bloc : allocation à loupé\n");
        #endif
        return -1;
    }
    inode->dateDerAcces = time(NULL);
    inode->dateDerModif = time(NULL);
    inode->taille = taille;
    return EcrireContenuBloc(*BlocDonnees(inode), contenu, taille);
}

long LireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille){
    if (inode == NULL || contenu == NULL || taille < 0) {
        #ifdef DEBUG
        fprintf(stderr,"LireDonneesInode1bloc : paramètres invalides\n");
        #endif
        return -1;
    }
    if (inode->blocDonnees[0]==NULL){
        #ifdef DEBUG
        fprintf(stderr,"LireDonneesInode1bloc : allocation à loupé\n");
        #endif
        return -1;
    }
    inode->dateDerAcces = time(NULL);
    return LireContenuBloc(*BlocDonnees(inode), contenu, taille);
}
