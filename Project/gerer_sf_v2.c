#include "sf.h"
#include <stdio.h>

#define NOMBRE_SF_TEST 100000

/*
 TEST():
 Si le test retourne 1 affiche un message sur stderr si la macro DEBUG n'est pas presente
 Le programe retourne 1 passant au shell l'information d'une erreur
 */
#ifndef DEBUG
#define TEST(NomFonctionTest,ParametreFonction,TypeDebug) if (NomFonctionTest(ParametreFonction)){ \
    fprintf(stderr, "%s à loupé, make %s à peut-être plus d'information\n",#NomFonctionTest,TypeDebug);\
        return 1;}
#else
#define TEST(NomFonctionTest,ParametreFonction,TypeDebug) if (NomFonctionTest(ParametreFonction))return 1;
#endif

static int TestCreerSF(tSF adresse[]){
    for (int i = 0;i<NOMBRE_SF_TEST;i++){
        adresse[i] = CreerSF("nvme0");
    }
    return 0;
}

static int TestDetruireSF(tSF adresse[]){
    for (int i = 0;i<NOMBRE_SF_TEST;i++){
        DetruireSF(&adresse[i]);
    }
    return 0;
}

static int TestAfficherSF(void){
    tSF sf = CreerSF("nvme");
    AfficherSF(sf);
    DetruireSF(&sf);
    return 0;
}

int main(void){
    tSF adresseSF[NOMBRE_SF_TEST];

    printf("Lancement de La batterie de test ....\n");
    printf("Test des fonctions Systeme Fichier [1/2]...\n");

    TEST(TestCreerSF, adresseSF, "sanatize");
    TEST(TestDetruireSF, adresseSF, "sanatize");
    TEST(TestAfficherSF,, "debug");

    printf("Tout les tests sont passé avec succes ....\n");
    return 0;
}
