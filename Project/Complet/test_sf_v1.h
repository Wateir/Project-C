#ifndef __TEST_SF_V1_H__
#define __TEST_SF_V1_H__
#include "inode.h"

//NOMBRE_BLOC_TEST et NOMBRE_INODE_TEST si trop important peuvent causer un ralentissement du systeme
#define NOMBRE_BLOC_TEST 100000
#define NOMBRE_INODE_TEST 10000
#define NOMBRE_STRING_TEST 3

extern int TestCreerBloc(tBloc adresse[]);

extern int TestDetruireBloc(tBloc adresse[]);

/*
 TEST_ECRITURE :
 initialise un tableau d'unsigned char avec la chaine de charactère donnée en paramètre,
 l'ecris dans un bloc avec la fonction qu'on voudra tester
 compare le contenu de la chaine de caractère et du bloc pour savoir s'il sont identique
 ecris un message si erreur
 */
extern int TestEcrireContenuBloc(unsigned char** string);

extern int TestLireContenuBloc(unsigned char** string);

extern int TestCreerInode(tInode adresse[]);

extern int TestDetruireInode(tInode adresse[]);

extern int TestNumero(tInode adresse[]);

extern int TestDateDerAcces(tInode adresse[]);

extern int TestDateDerModif(tInode adresse[]);

extern int TestDateDerModifFichier(tInode adresse[]);

extern int TestType(tInode adresse[]);

extern int TestTaille(tInode adresse[]);

extern int TestAfficherInode(void);

extern int TestEcrireDonneesInode1bloc(void);

extern int TestLireDonneesInode1bloc(void);

#endif
