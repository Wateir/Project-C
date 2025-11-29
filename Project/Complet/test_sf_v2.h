#ifndef __TEST_SF_V2_H__
#define __TEST_SF_V2_H__

#include "sf.h"

#define CHEMIN_ACCES "./Fichier/"
#define TAILLE_CHEMIN 256
#define NOMBRE_SF_TEST 100000

extern int TestCreerSF(tSF adresse[]);

extern int TestDetruireSF(tSF adresse[]);

extern int TestAfficherSF(void);

extern int TestEcrire1BlocFichierSF(void);

#endif
