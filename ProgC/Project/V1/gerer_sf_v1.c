#include "inode.h"
#include "bloc.h"

#include <stdlib.h>
#include <string.h>
//NOMBRE_BLOC_TEST et NOMBRE_INODE_TEST si trop important peuvent causer un ralentissement du systeme
#define NOMBRE_BLOC_TEST 100000
#define NOMBRE_INODE_TEST 10000
#define NOMBRE_STRING_TEST 3

#define TEST(NomFonctionTest,ParametreFonction,TypeDebug) \
    if (NomFonctionTest(ParametreFonction)){ \
        fprintf(stderr, "%s à loupé, make %s à peut-être plus d'information\n",#NomFonctionTest,TypeDebug);\
        return 1;}

int TestCreerBloc(tBloc adresse[]){
    for (int i = 0;i<NOMBRE_BLOC_TEST;i++){
        adresse[i] = CreerBloc();
        if (adresse[i]==NULL){
            return 1;
        }
    }
    return 0;
}

int TestDetruireBloc(tBloc adresse[]){
    for(int i = 0;i<NOMBRE_BLOC_TEST;i++){
        DetruireBloc(&adresse[i]);
    }
    return 0;
}

/*
 TEST_ECRITURE :
 initialise un tableau d'unsigned char avec la chaine de charactère donnée en paramètre,
 l'ecris dans un bloc avec la fonction qu'on voudra tester
 compare le contenu de la chaine de caractère et du bloc pour savoir s'il sont identique
 ecris un message si erreur
 */
 int TestEcritureContenuBLocAux(unsigned char** string,tBloc bloc,int taille, int numero, char contenu[]){
    string[numero] = malloc(taille);
    strncpy((char*)string[numero], contenu, taille);
    EcrireContenuBloc(bloc,string[numero],taille);

    int retour = strcmp((char *) bloc,(char*)string[numero]);
    if (retour != 0){
        #ifdef DEBUG
        fprintf(stderr, "TestEcrireContenuBloc : [%s] et [%s] sont different\n",(char *) bloc,(char*)string[numero]);
        #endif
        return 1;
    }
    return 0;
}

int TestEcrireContenuBloc(unsigned char** string){
    tBloc bloc = CreerBloc();

    if (TestEcritureContenuBLocAux(string, bloc, 23+1,0, "Projet du module ProgC")){
        DetruireBloc(&bloc);
        return 1;
    }
    if (TestEcritureContenuBLocAux(string, bloc, 0+1,1, "")){
        DetruireBloc(&bloc);
        return 1;
    }
    if (TestEcritureContenuBLocAux(string, bloc, 5+1,2, "AAAAA")){
        DetruireBloc(&bloc);
        return 1;
    }

    DetruireBloc(&bloc);
    return 0;
}

int TestLireContenuBlocAux(unsigned char** string,tBloc bloc, int numero,int taille){
    unsigned char contenu[TAILLE_BLOC+1];
    LireContenuBloc(bloc,contenu,taille);

    int retour = strcmp((char *) contenu,(char*)string[numero]);
    if (retour != 0){
        #ifdef DEBUG
        fprintf(stderr, "TestLireContenuBloc : [%s] et [%s] sont different\n",(char *) bloc,(char*)string[numero]);
        #endif
        return 1;
    }
    return 0;
}

int TestLireContenuBloc(unsigned char** string){
    tBloc bloc = CreerBloc();

    EcrireContenuBloc(bloc,string[0],23+1);
    if (TestLireContenuBlocAux(string, bloc,0,23+1)){
        DetruireBloc(&bloc);
        free(string[0]);
        free(string[1]);
        free(string[2]);
        return 1;
    }
    free(string[0]);
    EcrireContenuBloc(bloc,string[1],0+1);
    if (TestLireContenuBlocAux(string, bloc,1,0+1)){
        DetruireBloc(&bloc);
        free(string[1]);
        free(string[2]);
        return 1;
    }
    free(string[1]);
    EcrireContenuBloc(bloc,string[2],5+1);
    if (TestLireContenuBlocAux(string, bloc,2,5+1)){
        DetruireBloc(&bloc);
        free(string[2]);
        return 1;
    }
    free(string[2]);

    DetruireBloc(&bloc);
    return 0;
}

int TestCreerInode(tInode adresse[]){
    for (int i = 0;i<NOMBRE_INODE_TEST;i++){
        adresse[i] = CreerInode(i, 2);
    }
    return 0;
}

int TestDetruireInode(tInode adresse[]){
    for(int i = 0;i<NOMBRE_INODE_TEST;i++){
        DetruireInode(&adresse[i]);
    }
    return 0;
}

int TestNumero(tInode adresse[]){
    for (int i=0;i<3;i++){
        adresse[i] = CreerInode(i, i);
        if (Numero(adresse[i])!=(unsigned int)i){
            #ifdef DEBUG
            fprintf(stderr, "TestNumero : [%d] et [%d] sont different\n",Numero(adresse[i]),i);
            #endif
            for (int j=i;j>=0;j--){;DetruireInode(&adresse[j]);}
            return 1;
        }
    }
    return 0;
}

int TestType(tInode adresse[]){
    for (int i=0;i<3;i++){
        if (Type(adresse[i])!=(unsigned int)i){
            #ifdef DEBUG
            fprintf(stderr, "TestType : [%d] et [%d] sont different\n",Type(adresse[i]),i);
            #endif
            for (int j=i;j<3;j++){ DetruireInode(&adresse[j]);}
            return 1;
            }
        DetruireInode(&adresse[i]);

    }
    return 0;
}

int TestEcrireDonneesInode1bloc(void){
    tInode inode = CreerInode(0, 0);
    unsigned char string[23+1] ="Projet du module ProgC";

    if (EcrireDonneesInode1bloc(inode, NULL, 23+1) != -1){
        #ifdef DEBUG
        fprintf(stderr, "TestEcrireDonneesInode1bloc : Retourne pas -1 avec contenu NULL\n");
        #endif
        DetruireInode(&inode);
        return 1;
    }
    if (EcrireDonneesInode1bloc(inode, string, 23+1) == -1){
        #ifdef DEBUG
        fprintf(stderr, "TestEcrireDonneesInode1bloc : [%s] n'a pas pu etre ecris\n",string);
        #endif
        DetruireInode(&inode);
        return 1;
    }
    DetruireInode(&inode);
    return 0;
}
int TestLireDonneesInode1bloc(void){
    tInode inode = CreerInode(0, 0);
    unsigned char string[23+1] ="Projet du module ProgC";

    if (LireDonneesInode1bloc(inode, NULL, 23+1) != -1){
        #ifdef DEBUG
        fprintf(stderr, "TestLireDonneesInode1bloc : Retourne pas -1 avec contenu NULL\n");
        #endif
        DetruireInode(&inode);
        return 1;
    }
    if (EcrireDonneesInode1bloc(inode, string, 23+1) == -1){
        #ifdef DEBUG
        fprintf(stderr, "TestLireDonneesInode1bloc : [%s] n'a pas pu etre ecris\n",string);
        #endif
        DetruireInode(&inode);
        return 1;
    }
    unsigned char contenu[TAILLE_BLOC+1];
    int retour;
    if ((retour = LireDonneesInode1bloc(inode,contenu,23+1)) != 23+1){
        #ifdef DEBUG
        fprintf(stderr, "TestLireDonneesInode1bloc : LireDonneesInode1bloc n'a pas retourner la bonne valeur : %d\n",retour);
        #endif
        DetruireInode(&inode);
        return 1;
    }
    if (strcmp((char *) string,(char*) contenu) != 0){
        #ifdef DEBUG
        fprintf(stderr, "TestLireDonneesInode1bloc : les chaines sont different\n");
        #endif
        DetruireInode(&inode);
        return 1;
    }
    DetruireInode(&inode);
    return 0;
}

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
    TEST(TestType, adresseTest, "debug");

    //TEST(TestAfficherInode,, "debug");
    TEST(TestEcrireDonneesInode1bloc,, "debug");
    TEST(TestLireDonneesInode1bloc,, "debug");


    printf("Tout les tests sont passé avec succes ....\n");
    return 0;
}
