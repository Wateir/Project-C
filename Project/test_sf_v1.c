#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "inode.h"
#include "test_sf_v1.h"

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
static int TestEcritureContenuBLocAux(unsigned char** string,tBloc bloc,int taille, int numero, char contenu[]){
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

static int TestLireContenuBlocAux(unsigned char** string,tBloc bloc, int numero,int taille){
    unsigned char contenu[100];
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

int TestDateDerAcces(tInode adresse[]){
    for (int i=0;i<3;i++){
        time_t temp;
        time(&temp);
        adresse[i]->dateDerAcces = temp;
        if (DateDerAcces(adresse[i])!=temp){
            #ifdef DEBUG
            fprintf(stderr, "TestDateDerAcces : [%ld] et [%ld] sont different\n",DateDerAcces(adresse[i]),temp);
            #endif
            for (int j=0;j<3;j++){;DetruireInode(&adresse[j]);}
            return 1;
        }
    }
    return 0;
}

int TestDateDerModif(tInode adresse[]){
    for (int i=0;i<3;i++){
        time_t temp;
        time(&temp);
        adresse[i]->dateDerModif = temp;
        if (DateDerModif(adresse[i])!=temp){
            #ifdef DEBUG
            fprintf(stderr, "TestDateDerModif : [%ld] et [%ld] sont different\n",DateDerModif(adresse[i]),temp);
            #endif
            for (int j=0;j<3;j++){;DetruireInode(&adresse[j]);}
            return 1;
        }
    }
    return 0;
}

int TestDateDerModifFichier(tInode adresse[]){
    for (int i=0;i<3;i++){
        time_t temp;
        time(&temp);
        adresse[i]->dateDerModifInode = temp;
        if (DateDerModifFichier(adresse[i])!=temp){
            #ifdef DEBUG
            fprintf(stderr, "TestDateDerModifFichier : [%ld] et [%ld] sont different\n",DateDerModifFichier(adresse[i]),temp);
            #endif
            for (int j=0;j<3;j++){ DetruireInode(&adresse[j]);}
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
    }
    return 0;
}

int TestTaille(tInode adresse[]){
    for (int i=0;i<3;i++){
        time_t temp;
        time(&temp); // J'utilise la date comme taille, au final le nombre importe peu pour le test, seul l'exactitude importe ici
        adresse[i]->taille = temp;
        if (Taille(adresse[i])!=temp){
            #ifdef DEBUG
            fprintf(stderr, "TestDateDerModifFichier : [%ld] et [%ld] sont different\n",Taille(adresse[i]),temp);
            #endif
            for (int j=0;j<3;j++){ DetruireInode(&adresse[j]);}
            return 1;
        }
        DetruireInode(&adresse[i]);
    }
    return 0;
}

int TestAfficherInode(void){
    tInode inode = CreerInode(2, 3);
    AfficherInode(inode);
    unsigned char string[23+1] ="Projet du module ProgC";
    EcrireDonneesInode1bloc(inode, string, 23+1);
    time_t temp;
    inode->dateDerAcces = time(&temp);
    inode->dateDerModif = time(&temp);
    inode->dateDerModifInode = time(&temp);
    AfficherInode(inode);
    DetruireInode(&inode);
    return 0;
}

int TestEcrireDonneesInode1bloc(void){
    tInode inode = CreerInode(0, 0);
    unsigned char string[23+1] ="Projet du module ProgC";

    if (EcrireDonneesInode1bloc(inode, NULL, 23+1) != -1){
        fprintf(stderr, "TestEcrireDonneesInode1bloc : Retourne pas -1 avec contenu NULL\n");
        DetruireInode(&inode);
        return 1;
    }
    if (EcrireDonneesInode1bloc(inode, string, 23+1) == -1){
        fprintf(stderr, "TestEcrireDonneesInode1bloc : [%s] n'a pas pu etre ecris\n",string);
        DetruireInode(&inode);
        return 1;
    }
    if (strcmp((char *) inode->blocDonnees[0], (char*)string) != 0){
        fprintf(stderr, "TestEcrireDonneesInode1bloc : [%s] et [%s] sont different\n",inode->blocDonnees[0],string);
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
        fprintf(stderr, "TestLireDonneesInode1bloc : Retourne pas -1 avec contenu NULL\n");
        DetruireInode(&inode);
        return 1;
    }
    if (EcrireDonneesInode1bloc(inode, string, 23+1) == -1){
        fprintf(stderr, "TestLireDonneesInode1bloc : [%s] n'a pas pu etre ecris\n",string);
        DetruireInode(&inode);
        return 1;
    }
    if (strcmp((char *) inode->blocDonnees[0], (char*)string) != 0){
        fprintf(stderr, "TestLireDonneesInode1bloc : [%s] et [%s] sont different\n",inode->blocDonnees[0],string);
        DetruireInode(&inode);
        return 1;
    }
    DetruireInode(&inode);
    return 0;
}
