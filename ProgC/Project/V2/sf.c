/**
 * ProgC - Projet Automne 25-26 : Gestion de systèmes de fichiers
 * VERSION 2
 * Fichier : sf.c
 * Module de gestion d'un systèmes de fichiers (simulé)
 **/

#include "sf.h"
#include "bloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Taille maximale du nom du SF (ou nom du disque)
#define TAILLE_NOM_DISQUE 24

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

// Définition du super-bloc
struct sSuperBloc
{
  // Le nom du disque (ou du système de fichiers) (avec le '\0')
  char nomDisque[TAILLE_NOM_DISQUE+1];
  // La date de dernière modification du système de fichiers
  time_t dateDerModif;
};

// Type représentant le super-bloc
typedef struct sSuperBloc *tSuperBloc;

// Définition de la liste chaînée des inodes
struct sListeInodes
{
  // Références vers le premier et le dernier élément de la liste chaînée
  struct sListeInodesElement *premier, *dernier;
  // Nombre d'inodes dans la liste
  int nbInodes;
};

// Définition d'un élement de la liste chaînée des inodes dans le SF
struct sListeInodesElement
{
  // L'inode proprement dit
  tInode inode;
  // L'élément suivant dans la liste chaînée
  struct sListeInodesElement *suivant;
};

// Définition d'un système de fichiers (simplifié)
struct sSF
{
  // Le super-bloc
  tSuperBloc superBloc;
  // La liste chaînée des inodes
  struct sListeInodes listeInodes;
};

/* V2
*  Crée et retourne un super-bloc.
* Fonction non publique (static)
* Entrée : le nom du disque (ou du SF)
* Sortie : le super-bloc, ou NULL en cas de problème
*/
static tSuperBloc CreerSuperBloc(char nomDisque[]){
    tSuperBloc bloc = malloc(sizeof(struct sSuperBloc));
    TEST_EXISTANCE(bloc,"CreerSuperBloc","probleme creation\n",NULL)
    strcpy(bloc->nomDisque, nomDisque);
    bloc->dateDerModif = time(NULL);
    return bloc;
}

/* V2
*  Détruit un super-bloc.
* Fonction non publique (static)
* Entrée : le super-bloc à détruire
* Sortie : aucune
*/
static void DetruireSuperBloc(tSuperBloc *pSuperBloc){
    free(*pSuperBloc);
    *pSuperBloc = NULL;
}

/* V2
*  Affiche le contenu d'un super-bloc.
* Fonction non publique (static)
* Entrée : le super-bloc à afficher
* Sortie : aucune
*/
static void AfficherSuperBloc(tSuperBloc superBloc){
    printf("taille bloc = %d, date der modif = %s\n",TAILLE_BLOC,ctime(&(superBloc)->dateDerModif));
}

static struct sListeInodesElement* CreerListeInodesElement(tInode inode){
    TEST_EXISTANCE(inode,"CreerListeInodesElement","L'inode n'existe pas\n",NULL)

    struct sListeInodesElement* liste = malloc(sizeof(struct sListeInodesElement));
    TEST_EXISTANCE(liste,"CreerListeInodesElement","L'allocation à loupé\n",NULL)
    liste->inode = inode;
    liste->suivant = NULL;
    return liste;
}

static void DetruireListeInodesElement(struct sListeInodesElement** liste){
    TEST_EXISTANCE(*liste,"DetruireListeInodesElement","la liste d'inode n'existe pas",)
    DetruireInode(&(*liste)->inode);
    free(*liste);
    *liste = NULL;
}

/* V2
 * Crée un nouveau système de fichiers.
 * Entrée : nom du disque à associer au système de fichiers créé
 * Retour : le système de fichiers créé, ou NULL en cas d'erreur
 */
 tSF CreerSF(char nomDisque[]){
     tSF sf = malloc(sizeof(struct sSF));
     TEST_EXISTANCE(sf,"CreerSF","L'allocation à loupé\n",NULL)

     sf->superBloc = CreerSuperBloc(nomDisque);
     sf->listeInodes.nbInodes = 0;
     sf->listeInodes.dernier = NULL;
     sf->listeInodes.premier = NULL;
     return sf;
 }

/* V2
 * Détruit un système de fichiers et libère la mémoire associée.
 * Entrée : le SF à détruire
 * Sortie : aucune
 */
 void DetruireSF(tSF *pSF) {
     TEST_EXISTANCE(*pSF,"DetruireSF","Tentative de free NULL",)
     DetruireSuperBloc(&((*pSF)->superBloc));

     struct sListeInodesElement *current = (*pSF)->listeInodes.premier;
     struct sListeInodesElement *temp;
     while (current != NULL) {
         temp = current->suivant;
         DetruireListeInodesElement(&current);
         current = temp;
     }

     (*pSF)->listeInodes.premier = NULL;
     free(*pSF);
     *pSF = NULL;
 }

/* V2
 * Affiche les informations relative à un système de fichiers i.e;
 * le contenu du super-bloc et celui des différents inodes du SF
 * Entrée : le SF à afficher
 * Sortie : aucune
 */
 void AfficherSF(tSF sf){
     TEST_EXISTANCE(sf,"AfficherSF","Le systeme de fichier n'existe pas\n",)

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
 }

 static tInode AjouterInodeSF(tSF sf,natureFichier type){
     tInode inode = CreerInode(sf->listeInodes.nbInodes+1, type);
     TEST_EXISTANCE(sf, "AjouterInodeSF", "l'allocation de l'inode à loupén", NULL);
     if(sf->listeInodes.nbInodes==0){
         sf->listeInodes.premier = CreerListeInodesElement(inode);
         sf->listeInodes.dernier = sf->listeInodes.premier;
     }
     else{
         struct sListeInodesElement* avantDernier = sf->listeInodes.dernier;
         avantDernier->suivant = CreerListeInodesElement(inode);
         sf->listeInodes.dernier = avantDernier->suivant;
     }
     sf->listeInodes.dernier->suivant = NULL;
     sf->listeInodes.nbInodes++;
     return inode;
 }

/* V2
 * Ecrit un fichier d'un seul bloc dans le système de fichiers.
 * Entrées : le système de fichiers, le nom du fichier (sur disque) et son type dans le SF (simulé)
 * Sortie : le nombre d'octets effectivement écrits, -1 en cas d'erreur.
 */
 long Ecrire1BlocFichierSF(tSF sf, char nomFichier[], natureFichier type) {
     TEST_EXISTANCE(sf, "Ecrire1BlocFichierSF", "Le système de fichier n'existe pas\n", -1);
     FILE *fichier = fopen(nomFichier, "rb");
     TEST_EXISTANCE(fichier, "Ecrire1BlocFichierSF", "L'ouverture du fichier a échoué\n", -1);

     fseek(fichier, 0, SEEK_END);
     long taille = ftell(fichier);
     fseek(fichier, 0, SEEK_SET);

     taille = ((taille > TAILLE_BLOC) ? TAILLE_BLOC : taille);

     tInode inode = AjouterInodeSF(sf, type);
     TEST_EXISTANCE(inode, "Ecrire1BlocFichierSF", "L'allocation de l'inode a échoué\n", -1);
     unsigned char *tampon = malloc(taille);
     TEST_EXISTANCE(tampon, "Ecrire1BlocFichierSF", "L'allocation du tampon a échoué\n", -1);

     if((long)fread(tampon, 1, taille, fichier)!=taille)
     RETOURNE_ERREUR("Ecrir1BlocFichierSF",-1,"fread a renvoyer une taille erroné\n",free(tampon);fclose(fichier);)

     fclose(fichier);
     sf->superBloc->dateDerModif = time(NULL);
     long res;
     if((res = EcrireDonneesInode1bloc(inode, tampon, taille))!=taille)
     RETOURNE_ERREUR("Ecrire1BlocFichierSF",-1,"EcireDonneesInode1bloc a renvoyer une taille erroné\n",free(tampon);)

     free(tampon);
     return res;
 }
