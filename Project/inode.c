#include <stdio.h>
#include <stdlib.h>
#ifdef DEBUG
#include <string.h>
#endif
#include <time.h>
#include "inode.h"
#include "macro.h"

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
    TEST_EXISTANCE(bloc,"EcrireContenuBloc","le bloc n'existe pas",-1)
    int i;
    for (i=0;i<taille && i<TAILLE_BLOC;i++){
        bloc[i] = contenu[i];
    }
    return (long) i;
}

//Reimplementation de EcrireContenuBloc permetant un decallage
static long ReEcrireContenuBloc(tBloc bloc,const unsigned char *contenu,const long taille,const long decallage){
    TEST_EXISTANCE(bloc,"EcrireContenuBloc","le bloc n'existe pas",-1)
    int i;
    for (i=decallage;i<taille && i<TAILLE_BLOC;i++){
        bloc[i] = contenu[i];
    }
    return (long) i;
}

long LireContenuBloc(tBloc bloc, unsigned char *contenu, long taille){
    TEST_EXISTANCE(bloc,"LireContenuBloc","le bloc n'existe pas",-1)
    int i;
    for (i=0;i<taille||i<TAILLE_BLOC;i++){
        contenu[i] = bloc[i];
    }
    return (long) i;
}

int SauvegarderBloc(tBloc bloc, long taille, FILE *fichier){
    TEST_EXISTANCE(fichier,"SauvegarderBloc","le fichier n'existe pas",-1)
    TEST_EXISTANCE(bloc,"SauvegarderBloc","le bloc n'existe pas",-1)

    int valRetour;
    for(int i=0;i<taille;i++){
        valRetour =  putc(bloc[i], fichier);
        if (valRetour == EOF){
            #if DEBUG
            fprintf(stderr," SauvegarderBlo : l'ecriture a echoué");
            #endif
            return -1;
        }
    }

    return 0;
}

int ChargerBloc(tBloc bloc, long taille, FILE *fichier){
    TEST_EXISTANCE(fichier,"SauvegarderBloc","le fichier n'existe pas",-1)
    TEST_EXISTANCE(bloc,"SauvegarderBloc","le bloc n'existe pas",-1)
    int valRetour;
    for(int i=0;i<taille;i++){
        valRetour = getc(fichier);
        if (valRetour == EOF){
            #ifdef DEBUG
            fprintf(stderr,"ChargerBloc : la lecture à loupé\n");
            #endif
            printf("vide");
            return -1;
        }
        else{
            bloc[i]=valRetour;
        }
    }
    return 0;
}

//Retourne le bloc à l'inode (inode)
static unsigned char** BlocDonnees(const tInode inode){
    TEST_EXISTANCE(inode,"BlocDonnees","l'inode n'existe pas",NULL)
    inode->dateDerAcces = time(NULL);
    return inode->blocDonnees;
}

tInode CreerInode(unsigned int numInode, natureFichier type){
    tInode inode= malloc(sizeof(struct sInode));
    if (inode == NULL){
        fprintf(stderr," CreerInode : probleme creation");
        return NULL;
    }
    BlocDonnees(inode)[0]= NULL; // on initialise a NULL pour etre sur que si c'est pas changer, Detruire vera la non initialisation
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
    TEST_EXISTANCE(inode,"Numero","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->numero;
}

time_t DateDerAcces(tInode inode){
    TEST_EXISTANCE(inode,"DateDerAcces","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->dateDerAcces;
}

time_t DateDerModif(tInode inode){
    TEST_EXISTANCE(inode,"DateDerModif","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->dateDerModif;
}

time_t DateDerModifFichier(tInode inode){
    TEST_EXISTANCE(inode,"DateDerModifFichier","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->dateDerModifInode;
}

natureFichier Type(tInode inode){
    TEST_EXISTANCE(inode,"Type","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->type;
}


long Taille(tInode inode){
    TEST_EXISTANCE(inode,"Taille","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->taille;
}

//Retourne le string associé au type (type)
static const char* stringNatureFichier(const natureFichier type){
    if(type == 0) return "ORDINAIRE";
    if(type == 1) return "REPERTOIRE";
    return "AUTRE";
}

void AfficherInode(tInode inode){
    if (inode==NULL){
        #ifdef DEBUG
        fprintf(stderr,"AfficherInode : inode->blocDonnees[0] est vide\n");
        #endif
        printf("vide");
        return;
    }
    if (BlocDonnees(inode)[0]==NULL){
        #ifdef DEBUG
        fprintf(stderr,"AfficherInode : inode->blocDonnees[0] est vide\n");
        #endif
        return;
    }
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
    for (int i=0;BlocDonnees(inode)[i]!=NULL;i++){
        printf("%s\n",BlocDonnees(inode)[i]);
    }
    inode->dateDerAcces = time(NULL);
}

long EcrireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille){
    if (inode == NULL || contenu == NULL || taille < 0) {
        #ifdef DEBUG
        fprintf(stderr,"EcrireDonneesInode1bloc : paramètres invalides\n");
        #endif
        return -1;
    }
    if (BlocDonnees(inode)[0]==NULL){
        BlocDonnees(inode)[0] = CreerBloc();
        if (BlocDonnees(inode)[0]==NULL){
            #ifdef DEBUG
            fprintf(stderr,"EcrireDonneesInode1bloc : allocation à loupé\n");
            #endif
            return -1;
        }
    }
    inode->taille = taille = EcrireContenuBloc(BlocDonnees(inode)[0], contenu, taille);
    BlocDonnees(inode)[1] = NULL;
    inode->dateDerAcces = time(NULL);
    inode->dateDerModif = time(NULL);
    return Taille(inode);

}

long LireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille){
    if (inode == NULL || contenu == NULL || taille < 0) {
        #ifdef DEBUG
        fprintf(stderr,"LireDonneesInode1bloc : paramètres invalides\n");
        #endif
        return -1;
    }
    if (BlocDonnees(inode)[0]==NULL){
        #ifdef DEBUG
        fprintf(stderr,"LireDonneesInode1bloc : rien à lire\n");
        #endif
        return -1;
    }
    //Les deux dernières lignes dans ce sens suppose qu'on assume que cela prendra moins d'une seconde a être realisé
    inode->dateDerAcces = time(NULL);
    return LireContenuBloc(BlocDonnees(inode)[0], contenu, taille);
}

//Retourne la chaine de charactère amputé de (debutDecoupage) caractère
static unsigned char* CouperChaine(unsigned char string[],int debutDecoupage,long taille){
    unsigned char* copyCouper = malloc(taille* sizeof(char));
    if (copyCouper == NULL){
        #ifdef DEBUG
        fprintf(stderr,"CouperChaine : allocation à loupé\n");
        #endif
        return NULL;
    }
    int j=0;
    for(int i = debutDecoupage;i<taille;i++){
        copyCouper[j]=string[i];
        j++;
    }
    return copyCouper;
}

long EcrireDonneesInode(tInode inode, unsigned char *contenu, long taille, long decalage){
    if (inode == NULL || contenu == NULL || taille < 0) {
        #ifdef DEBUG
        fprintf(stderr,"EcrireDonneesInodebloc : paramètres invalides\n");
        #endif
        return -1;
    }
    long resteEcrire = taille;
    long resteDecallage = decalage;
    int i;
    for(i=0;BlocDonnees(inode)[i]!=NULL&&i<NB_BLOCS_DIRECTS;i++){
        if (BlocDonnees(inode)[i] == NULL){
            BlocDonnees(inode)[i] = CreerBloc();
            if (BlocDonnees(inode)[i]==NULL){
                #ifdef DEBUG
                fprintf(stderr,"EcrireDonneesInodebloc : allocation à loupé\n");
                #endif
                return -1;
            }
        }
        if (resteDecallage>= TAILLE_BLOC){
            resteDecallage -= TAILLE_BLOC;
        }
        else{
            resteEcrire -= ReEcrireContenuBloc(BlocDonnees(inode)[i],CouperChaine(contenu,taille-resteEcrire,resteEcrire),resteEcrire,resteDecallage);
        }
    }
    //On s'assure que le dernier bloc non ecris est initialisé à NULL
    if (i<NB_BLOCS_DIRECTS+1) inode->blocDonnees[i+1] = NULL;
    inode->dateDerModif = time(NULL);
    inode->dateDerAcces = time(NULL);
    return taille-resteEcrire;
}

int SauvegarderInode(tInode inode, FILE *fichier){
    TEST_EXISTANCE(fichier,"SauvegarderInode","le fichier n'existe pas",-1)
    TEST_EXISTANCE(inode,"SauvegarderInode","l'inode n'existe pas",-1)

    long resteEcrire = Taille(inode),valRetour;
    fprintf(fichier,"numero = %d\ntype = %d\ntaille = %ld",Numero(inode),Type(inode),Taille(inode));
    for (int i=0;BlocDonnees(inode)[i]!=NULL;i++){
        valRetour = SauvegarderBloc((tBloc) BlocDonnees(inode),resteEcrire,fichier);
        if (valRetour == -1){
            #ifdef DEBUG
            fprintf(stderr,"SauvegarderInode : erreur sur l'ecriture du bloc\n");
            #endif
            return -1;
        }
        resteEcrire -=valRetour;
    }

    return resteEcrire;
}
