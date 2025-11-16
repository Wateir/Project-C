#ifndef __INODE_H__
#define __INODE_H__

#include <time.h>

# define NB_BLOCS_DIRECTS 10 //Nombre maximum de blocs directs dans un inode
# define TAILLE_BLOC 64 //Taille d’un bloc en octets

//Type représentant un inode
typedef struct sInode * tInode ;
//Type public représentant un bloc de données
typedef unsigned char * tBloc ;

//Type représentant la nature d’un fichier
typedef enum{
    ORDINAIRE,
    REPERTOIRE,
    AUTRE
} natureFichier;

//Structure représentant un inode
struct sInode
{
    unsigned int numero ; //Numéro de l’inode
    natureFichier type ; //Le type du fichier : ordinaire , répertoire ou autre
    long taille ;//La taille en octets du fichier
    tBloc blocDonnees[NB_BLOCS_DIRECTS]; //Les adresses directes vers les blocs (NB_BLOCS_DIRECTS au maximum)
    time_t dateDerAcces , dateDerModif , dateDerModifInode ; //Les dates
};


//Crée et retourne un nouveau bloc de données
extern tBloc CreerBloc(void);

//Libère la mémoire allouée
extern void DetruireBloc(tBloc *pBloc);

//Copie dans le bloc (bloc), passé en paramètre, les taille octets situés à l’adresse contenu
extern long EcrireContenuBloc(tBloc bloc, unsigned char *contenu, long taille);

//Copie à l’adresse contenu les taille octets stockés dans le bloc bloc, passé en paramètre
extern long LireContenuBloc(tBloc bloc, unsigned char *contenu, long taille);

//Crée et retourne un inode à partir des informations données en paramètre : un numéro d’inode (numInode) et la nature du fichier associé à cet inode (type)
extern tInode CreerInode(unsigned int numInode, natureFichier type);

//Libère la mémoire alloué
extern void DetruireInode(tInode* pInode);

//Retourne le numéro de l’inode (inode)
extern unsigned int Numero(tInode inode);

//Retourne la date de dernier accès à l’inode (inode)
extern time_t DateDerAcces(tInode inode);

//Retourne la date de dernière modification de l’inode (inode)
extern time_t DateDerModif(tInode inode);

//Retourne la date de dernière modification du fichier associé à l’inode (inode)
extern time_t DateDerModifFichier(tInode inode);

//Retourne le type du fichier associé à l’inode (inode)
extern natureFichier Type(tInode inode);

//Retourne la taille du fichier associé à l’inode (inode)
extern long Taille(tInode inode);

//Affiche le contenu de l’inode (inode)
extern void AfficherInode(tInode inode);

//Copie dans l’inode inode, passé en paramètre, les taille octets situés à l’adresse contenu
extern long EcrireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille);

//Copie à l’adresse contenu les taille octets stockés dans l’inode (inode), passé en paramètre
extern long LireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille);
#endif
