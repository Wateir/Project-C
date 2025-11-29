#ifndef __TEST_SF_V3_H__
#define __TEST_SF_V3_H__

#define CHEMIN_ACCES "./Fichier/"
#define TAILLE_CHEMIN 256

extern int TestSauvegarderBloc(void);

extern int TestChargerBloc(void);

extern int TestEcrireDonneesInode(void);

extern int TestLireDonneesInode(void);

extern int TestSauvegarderInode(void);

extern int TestChargerInode(void);

extern int TestEcrireFichierSF(void);

extern int TestSauvegarderSF(void);

extern int TestChargerSF(void);

#endif
