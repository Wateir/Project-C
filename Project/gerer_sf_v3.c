#include "macro.h"

#include <stdio.h>

#include "test_sf_v1.h"
#include "test_sf_v2.h"
#include "test_sf_v3.h"


int main(void){
    tSF adresseSF[NOMBRE_SF_TEST];
    tBloc adresseBloc[NOMBRE_BLOC_TEST];
    tInode adresseInode[NOMBRE_INODE_TEST];
    unsigned char* string[NOMBRE_STRING_TEST];
    tInode adresseTest[3];

    printf("Lancement de La batterie de test ....\n");

    printf("Test des fonctions bloc [1/3]...\n");
    TEST(TestCreerBloc, adresseBloc, "sanatize");
    TEST(TestDetruireBloc, adresseBloc, "sanatize");
    TEST(TestEcrireContenuBloc, string, "debug");
    TEST(TestLireContenuBloc, string, "debug");

    TEST(TestSauvegarderBloc,,"debug");
    TEST(TestChargerBloc,,"debug");

    printf("Test des fonctions inode [2/3]...\n");

    TEST(TestCreerInode, adresseInode, "sanatize");
    TEST(TestDetruireInode, adresseInode, "sanatize");

    TEST(TestNumero, adresseTest, "debug");
    TEST(TestDateDerAcces, adresseTest, "debug");
    TEST(TestDateDerModif, adresseTest, "debug");
    TEST(TestDateDerModifFichier, adresseTest, "debug");
    TEST(TestType, adresseTest, "debug");
    TEST(TestTaille, adresseTest, "debug");

    TEST(TestAfficherInode,, "debug");
    TEST(TestEcrireDonneesInode1bloc,, "debug");
    TEST(TestLireDonneesInode1bloc,, "debug");

    TEST(TestEcrireDonneesInode,,"debug");
    TEST(TestLireDonneesInode,,"debug");
    TEST(TestSauvegarderInode,,"debug");
    TEST(TestChargerInode,,"debug");

    printf("Test des fonctions Systeme Fichier [3/3]...\n");

    TEST(TestCreerSF, adresseSF, "sanatize");
    TEST(TestDetruireSF, adresseSF, "sanatize");
    TEST(TestAfficherSF,, "debug");

    TEST(TestEcrireFichierSF,,"debug");
    TEST(TestSauvegarderSF,,"debug");
    TEST(TestChargerSF,,"debug");

    printf("Tout les tests sont passé avec succes ....\n");
    return 0;
}
