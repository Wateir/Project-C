#include "inode.h"
#include "macro.h"

#include <stdio.h>

#include "test_sf_v1.h"

//Les fonctions de test qui ne font que de l'affichage ne sont pas activé, leur reussite n'est pas testé
int main(void){
    tBloc adresseBloc[NOMBRE_BLOC_TEST];
    tInode adresseInode[NOMBRE_INODE_TEST];
    unsigned char* string[NOMBRE_STRING_TEST];
    tInode adresseTest[3];

    printf("Lancement de La batterie de test ....\n");

    printf("Test des fonctions bloc [1/2]...\n");
    TEST(TestCreerBloc, adresseBloc, "sanatize");
    TEST(TestDetruireBloc, adresseBloc, "sanatize");
    TEST(TestEcrireContenuBloc, string, "debug");
    TEST(TestLireContenuBloc, string, "debug");

    printf("Test des fonctions inode [2/2]...\n");

    TEST(TestCreerInode, adresseInode, "sanatize");
    TEST(TestDetruireInode, adresseInode, "sanatize");

    TEST(TestNumero, adresseTest, "debug");
    TEST(TestDateDerAcces, adresseTest, "debug");
    TEST(TestDateDerModif, adresseTest, "debug");
    TEST(TestDateDerModifFichier, adresseTest, "debug");
    TEST(TestType, adresseTest, "debug");
    TEST(TestTaille, adresseTest, "debug");

    //TEST(TestAfficherInode,, "debug");
    TEST(TestEcrireDonneesInode1bloc,, "debug");
    TEST(TestLireDonneesInode1bloc,, "debug");


    printf("Tout les tests sont passé avec succes ....\n");
    return 0;
}
