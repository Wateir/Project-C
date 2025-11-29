#ifndef __SF_H__
#define __SF_H__

#include "inode.h"

# define TAILLE_NOM_DISQUE 24 // Taille maximale du nom du disque du super - bloc

typedef struct sSF * tSF ;
typedef struct sSuperBloc * tSuperBloc ;

// Le super-bloc
struct sSuperBloc{
    char nomDisque [TAILLE_NOM_DISQUE+1]; // Le nom du système de fichiers ( disque )
    time_t dateDerModif ; // La date de dernière modification du système de fichiers
};

struct sListeInodes{
    struct sListeInodesElement * premier , * dernier ; //Références vers le premier et dernier élément-inode de la liste chaînée
    int nbInodes ; // Nombre d’inodes dans la liste chaînée
};

struct sListeInodesElement {
    tInode inode ; // L’inode proprement dit
    struct sListeInodesElement * suivant ; // L’élément suivant de la liste chaînée
};

struct sSF{
    tSuperBloc superBloc ; // Le super-bloc
    struct sListeInodes listeInodes ; // La liste chaînée des inodes constituant le système de fichiers
};

//Crée et retourne un nouveau système de fichiers ayant pour nom nomDisque
extern tSF CreerSF(char nomDisque[]);

//Détruit le système de fichiers référencé par le paramètre pSF
extern void DetruireSF(tSF *pSF);

//Affiche les informations relatives au système de fichiers passé en paramètre
extern void AfficherSF(tSF sf);

//Ecrit le contenu d’un fichier
extern long Ecrire1BlocFichierSF(tSF sf, char nomFichier[], natureFichier type);

//Ecrit un fichier dans le système de fichiers sf passé en paramètre.
extern long EcrireFichierSF(tSF sf, char nomFichier[], natureFichier type);

//Sauvegarde le système de fichiers paramètre dans un fichier de nom nomFichier
extern int SauvegarderSF(tSF sf, char nomFichier[]);

//Charge un système de fichiers depuis un fichier (sur disque) de nom nomFichier
extern int ChargerSF(tSF *pSF, char nomFichier[]);

#endif
