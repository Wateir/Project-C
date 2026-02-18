/**
 * ProgC - Projet Automne 25-26 : Gestion de systèmes de fichiers
 * VERSION 1
 * Fichier : inode.c
 * Module de gestion des inodes.
 **/
#include "inode.h"
#include "bloc.h"

#include <stdlib.h>

#ifdef DEBUG
#define TEST_EXISTANCE(pointeur,NomFonction,MessageErreur,ValeurRetour) \
    if ((pointeur) == NULL) { \
        fprintf(stderr, "%s : %s\n", NomFonction, MessageErreur); \
        return ValeurRetour;\
    }
#else
#define TEST_EXISTANCE(pointeur,NomFonction,MessageErreur,ValeurRetour)\
    if ((pointeur) == NULL) { \
    return ValeurRetour;\
    }
#endif

#ifdef DEBUG
#define RETOURNE_ERREUR(NomFonction,ValeurRetour,MessageErreur,EtapeOptionnel){\
    fprintf(stderr, "%s : %s", #NomFonction, MessageErreur); \
    EtapeOptionnel \
    return ValeurRetour;\
    }
#else
#define RETOURNE_ERREUR(NomFonction,ValeurRetour,MessageErreur,EtapeOptionnel){\
    EtapeOptionnel \
    return ValeurRetour;\
    }
#endif

// Nombre maximal de blocs dans un inode
#define NB_BLOCS_DIRECTS 10

// Définition d'un inode
struct sInode
{
  // Numéro de l'inode
  unsigned int numero;
  // Le type du fichier : ordinaire, répertoire ou autre
  natureFichier type;
  // La taille en octets du fichier
  long taille;
  // Les adresses directes vers les blocs (NB_BLOCS_DIRECTS au maximum)
  tBloc blocDonnees[NB_BLOCS_DIRECTS];
  // Les dates : dernier accès à l'inode, dernière modification du fichier
  // et de l'inode
  time_t dateDerAcces, dateDerModif, dateDerModifInode;
};

//Retourne le bloc à l'inode (inode)
static unsigned char** BlocDonnees(const tInode inode){
    TEST_EXISTANCE(inode,"BlocDonnees","l'inode n'existe pas",NULL)
    inode->dateDerAcces = time(NULL);
    return inode->blocDonnees;
}

/* V1
 * Crée et retourne un inode.
 * Entrées : numéro de l'inode et le type de fichier qui y est associé
 * Retour : l'inode créé ou NULL en cas de problème
 */
tInode CreerInode(int numInode, natureFichier type) {
    tInode inode= malloc(sizeof(struct sInode));
    TEST_EXISTANCE(inode,"CreerInode","probleme creation\n",NULL)

    for(int i=0;i<NB_BLOCS_DIRECTS;i++) BlocDonnees(inode)[i]= NULL;
    // on initialise a NULL pour etre sur que si c'est pas changer, Detruire vera la non initialisation
    inode->numero = numInode;
    inode->type = type;
    inode->dateDerModifInode = time(NULL);

    return inode;
}

/* V1
 * Détruit un inode.
 * Entrée : l'inode à détruire
 * Retour : aucun
 */
void DetruireInode(tInode *pInode) {
    for (int i=0;i<NB_BLOCS_DIRECTS;i++){
        if ((*pInode)->blocDonnees[i] != NULL){
            DetruireBloc(&(*pInode)->blocDonnees[i]);
        }
    }
    free(*pInode);
    *pInode = NULL;
}

/* V1
 * Récupère la date de dernier accès à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la date de dernier accès
 * Retour : la date de dernier accès à l'inode
 */
time_t DateDerAcces(tInode inode) {
    TEST_EXISTANCE(inode,"DateDerAcces","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->dateDerAcces;
}

/* V1
 * Récupère la date de dernière modification d'un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la date de dernière modification
 * Retour : la date de dernière modification de l'inode
 */
time_t DateDerModif(tInode inode) {
    TEST_EXISTANCE(inode,"DateDerModif","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->dateDerModif;
}

/* V1
 * Récupère la date de dernière modification d'u fichier associé à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la date de dernière modification du fichier associé
 * Retour : la date de dernière modification du fichier associé à l'inode
 */
time_t DateDerModifFichier(tInode inode) {
    TEST_EXISTANCE(inode,"DateDerModifFichier","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->dateDerModifInode;
}

/* V1
 * Récupère le numéro d'un inode.
 * Entrée : l'inode pour lequel on souhaite connaître le numéro
 * Retour : le numéro de l'inode
 */
unsigned int Numero(tInode inode) {
    TEST_EXISTANCE(inode,"Numero","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->numero;
}

/* V1
 * Récupère la taille en octets du fichier associé à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la taille
 * Retour : la taille en octets du fichier associé à l'inode
 */
long Taille(tInode inode) {
    TEST_EXISTANCE(inode,"Taille","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->taille;
}

/* V1
 * Récupère le type du fichier associé à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître le tyep de fichier associé
 * Retour : le type du fichier associé à l'inode
 */
natureFichier Type(tInode inode) {
    TEST_EXISTANCE(inode,"Type","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->type;
}

//Retourne le string associé au type (type)
static const char* stringNatureFichier(const natureFichier type){
    if(type == 0) return "ORDINAIRE";
    if(type == 1) return "REPERTOIRE";
    return "AUTRE";
}

/* V1
 * Affiche les informations d'un inode
 * Entrée : l'inode dont on souhaite afficher les informations
 * Retour : aucun
 */
void AfficherInode(tInode inode) {
    TEST_EXISTANCE(inode,"AfficherInode","L'inode n'existe pas \n",)
    TEST_EXISTANCE(BlocDonnees(inode)[0],"AfficherInode","inode->blocDonnees[0] est vide",)
    if (Taille(inode)<0)
    RETOURNE_ERREUR("AfficherInode",,"taille negative\n",printf("vide\n");)

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

/* V1
 * Copie à l'adresse contenu les taille octets stockés dans un inode.
 * Si taille est supérieure à la taille d’un bloc, seuls les TAILLE_BLOC premiers octets doivent être copiés.
 * Entrées : l'inode, l'adresse de la zone où recopier et la taille en octets de l'inode
 * Retour : le nombre d'octets effectivement lus dans l'inode ou -1 en cas d'erreur
 */
long LireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille) {
    if (inode == NULL || contenu == NULL || taille < 0)
    RETOURNE_ERREUR("LireDonneesInode1bloc",-1,"paramètres invalides\n",)
    TEST_EXISTANCE(BlocDonnees(inode)[0],"LireDonneesInode1bloc"," rien à lire\n",-1)
    //Les deux dernières lignes dans ce sens suppose qu'on assume que cela prendra moins d'une seconde a être realisé
    inode->dateDerAcces = time(NULL);
    return LireContenuBloc(BlocDonnees(inode)[0], contenu, taille);
}

/* V1
 * Copie dans un inode les taille octets situés à l’adresse contenu.
 * Si taille est supérieure à la taille d’un bloc, seuls les TAILLE_BLOC premiers octets doivent être copiés.
 * Entrées : l'inode, l'adresse de la zone à recopier et sa taille en octets
 * Retour : le nombre d'octets effectivement écrits dans l'inode ou -1 en cas d'erreur
 */
long EcrireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille) {
    if (inode == NULL || contenu == NULL || taille < 0)
    RETOURNE_ERREUR("EcrireDonneesInode1bloc",-1,"paramètres invalides\n",)

    if (BlocDonnees(inode)[0]==NULL){
        BlocDonnees(inode)[0] = CreerBloc();
        if (BlocDonnees(inode)[0]==NULL)
        RETOURNE_ERREUR("EcrireDonneesInode1bloc",-1,"allocation à loupé\n",)
    }
    inode->taille = taille = EcrireContenuBloc(BlocDonnees(inode)[0], contenu, taille);
    BlocDonnees(inode)[1] = NULL;
    inode->dateDerAcces = time(NULL);
    inode->dateDerModif = time(NULL);
    return Taille(inode);
}
