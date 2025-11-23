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
    long i;
    for (i=decallage;i<taille && i<TAILLE_BLOC;i++){
        bloc[i] = contenu[i];
    }
    return i - decallage;
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
            fprintf(stderr," SauvegarderBloc : l'ecriture a echoué");
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
            fprintf(stderr,"ChargerBloc : la lecture à loupé au %dime caractère\n",i);
            #endif
            printf("vide\n");
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
    for(int i=0;i<NB_BLOCS_DIRECTS;i++) BlocDonnees(inode)[i]= NULL;
    // on initialise a NULL pour etre sur que si c'est pas changer, Detruire vera la non initialisation
    inode->numero = numInode;
    inode->type = type;
    inode->dateDerModifInode = time(NULL);

    return inode;
}

void DetruireInode(tInode* pInode){
    for (int i=0;i<NB_BLOCS_DIRECTS;i++){
    if ((*pInode)->blocDonnees[i] != NULL){
        free((*pInode)->blocDonnees[i]);
    }
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
        printf("vide\n");
        return;
    }
    if (BlocDonnees(inode)[0]==NULL){
        #ifdef DEBUG
        fprintf(stderr,"AfficherInode : inode->blocDonnees[0] est vide\n");
        #endif
        return;
    }
    if (Taille(inode)<0){
        #ifdef DEBUG
        fprintf(stderr,"AfficherInode : taille negative : %ld\n",Taille(inode));
        #endif
        printf("vide\n");
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

    long resteALire = Taille(inode);
    for (int i = 0; i < NB_BLOCS_DIRECTS; i++) {
        if (BlocDonnees(inode)[i] != NULL) {
            for (int j = 0; j < TAILLE_BLOC && resteALire > 0; j++) {
                putchar(BlocDonnees(inode)[i][j]);
                resteALire--;
            }
        }
    }
    printf("\n");

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

long EcrireDonneesInode(tInode inode, unsigned char *contenu, long taille, long decalage) {
    if (inode == NULL || contenu == NULL || taille < 0) {
        #ifdef DEBUG
        fprintf(stderr,"EcrireDonneesInode : paramètres invalides\n");
        #endif
        return -1;
    }
    long resteEcrire = taille;
    long iDecalage = decalage;
    int i = iDecalage / TAILLE_BLOC;
    long posDansBloc = iDecalage % TAILLE_BLOC;

    while (i < NB_BLOCS_DIRECTS && resteEcrire > 0) {
        if (inode->blocDonnees[i] == NULL) {
            inode->blocDonnees[i] = CreerBloc();
            if (inode->blocDonnees[i] == NULL) {
                #ifdef DEBUG
                fprintf(stderr,"EcrireDonneesInode : échec allocation bloc\n");
                #endif
                return (inode->taille = taille - resteEcrire);
            }
        }
        long espaceBloc = TAILLE_BLOC - posDansBloc;
        long aEcrire;
        if (resteEcrire < espaceBloc) {
            aEcrire = resteEcrire;
        } else {
            aEcrire = espaceBloc;
        }

        long ecrit = ReEcrireContenuBloc(inode->blocDonnees[i],contenu+ (taille- resteEcrire), aEcrire,posDansBloc);
        if (ecrit < 0) return (inode->taille = taille - resteEcrire);
        resteEcrire -= ecrit;
        posDansBloc = 0;
        i++;
    }

    inode->dateDerModif = time(NULL);
    inode->dateDerAcces = time(NULL);
    return (inode->taille = taille - resteEcrire);
}

long LireDonneesInode(tInode inode, unsigned char *contenu, long taille, long decalage){

    inode->dateDerAcces = time(NULL);
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
