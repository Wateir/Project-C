#include "inode.h"
#include "sf.h"
#include <stdio.h>

#ifndef DEBUG
#define TEST(NomFonctionTest,ParametreFonction,TypeDebug) \
    if (NomFonctionTest(ParametreFonction)){ \
        fprintf(stderr, "%s à loupé, make %s à peut-être plus d'information\n",#NomFonctionTest,TypeDebug);\
        return 1;}
#else
#define TEST(NomFonctionTest,ParametreFonction,TypeDebug) if (NomFonctionTest(ParametreFonction))return 1;
#endif

#define CHEMIN_ACCES "./"
#define TAILLE_CHEMIN 256
#define NOMBRE_SF_TEST 100000

int TestCreerSF(tSF adresse[]){
    for (int i = 0;i<NOMBRE_SF_TEST;i++){
        adresse[i] = CreerSF("nvme0");
    }
    return 0;
}

int TestDetruireSF(tSF adresse[]){
    for (int i = 0;i<NOMBRE_SF_TEST;i++){
        DetruireSF(&adresse[i]);
    }
    return 0;
}

int TestAfficherSF(void){
    tSF sf = CreerSF("nvme");
    AfficherSF(sf);
    DetruireSF(&sf);
    return 0;
}

static int TestEcrire1BlocFichierSFAux(char nomFichier[],int taille,char chaine[],tSF sf,natureFichier type){
    char chemin[TAILLE_CHEMIN];
    sprintf(chemin, "%s/%s", CHEMIN_ACCES,nomFichier);
    FILE* fichier = fopen(chemin,"w");
    if (fichier == NULL){
        #ifdef DEBUG
        fprintf(stderr, "TestEcrire1BlocFichierSFAux : L'ouverture du fichier à loupé\n");
        #endif
        return 1;
    }
    int valRetour = fwrite(chaine,sizeof(char),taille, fichier);
    if (valRetour!= taille){
        #ifdef DEBUG
        fprintf(stderr, "TestEcrire1BlocFichierSFAux : EcrireContenuBloc à loupé\n");
        #endif
        return 1;
    }
    fclose(fichier);

    if (Ecrire1BlocFichierSF(sf,chemin,type) != taille){
        return 1;
    }
    return 0;
}

int TestEcrire1BlocFichierSF(void){
    tSF sf = CreerSF("nvme0n1p2");

    if (TestEcrire1BlocFichierSFAux("fichier5.proj",22+1,"Projet du module ProgC",sf,2)!=0){
        DetruireSF(&sf);
        return 1;
    }
    if (TestEcrire1BlocFichierSFAux("fichier6.proj",0+1,"",sf,1)!=0){
        DetruireSF(&sf);
        return 1;
    }
    if (TestEcrire1BlocFichierSFAux("fichier7.proj",5+1,"AAAAA",sf,3)!=0){
        DetruireSF(&sf);
        return 1;
    }

    DetruireSF(&sf);
    return 0;
}

int main(void){
    tSF adresseSF[NOMBRE_SF_TEST];

    printf("Lancement de La batterie de test ....\n");

    TEST(TestCreerSF, adresseSF, "sanatize");
    TEST(TestDetruireSF, adresseSF, "sanatize");
    TEST(TestEcrire1BlocFichierSF,,"debug");
    TEST(TestAfficherSF,, "debug");

    printf("Tout les tests sont passé avec succes ....\n");
    return 0;
}
