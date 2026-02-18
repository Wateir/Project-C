#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "inode.h"
#include "macro.h"
#include "sf.h"

//Crée et retourne un super-bloc associé au SF de nom nomDisque
static tSuperBloc CreerSuperBloc(char nomDisque[]){
    tSuperBloc bloc = malloc(sizeof(struct sSuperBloc));
    TEST_EXISTANCE(bloc,"CreerSuperBloc","probleme creation\n",NULL)
    strcpy(bloc->nomDisque, nomDisque);
    bloc->dateDerModif = time(NULL);
    return bloc;
}

//affiche les informations contenues dans le super-bloc passé en paramètre
static void AfficherSuperBloc(tSuperBloc superBloc){
    printf("taille bloc = %d, date der modif = %s\n",TAILLE_BLOC,ctime(&(superBloc)->dateDerModif));
}

//Détruit le super-bloc référencé par le paramètre pSuperBloc
static void DetruireSuperBloc(tSuperBloc *pSuperBloc){
    free(*pSuperBloc);
    *pSuperBloc = NULL;
}

static struct sListeInodesElement* CreerListeInodesElement(tInode inode){
    TEST_EXISTANCE(inode,"CreerListeInodesElement","L'inode n'existe pas\n",NULL)

    struct sListeInodesElement* liste = malloc(sizeof(struct sListeInodesElement));
    TEST_EXISTANCE(liste,"CreerListeInodesElement","L'allocation à loupé\n",NULL)
    liste->inode = inode;
    liste->suivant = NULL;
    return liste;
}

static void DetruireListeInodesElement(struct sListeInodesElement** liste){
    TEST_EXISTANCE(*liste,"DetruireListeInodesElement","la liste d'inode n'existe pas",)
    DetruireInode(&(*liste)->inode);
    free(*liste);
    *liste = NULL;
}


tSF CreerSF(char nomDisque[]){
    tSF sf = malloc(sizeof(struct sSF));
    TEST_EXISTANCE(sf,"CreerSF","L'allocation à loupé\n",NULL)

    sf->superBloc = CreerSuperBloc(nomDisque);
    sf->listeInodes.nbInodes = 0;
    sf->listeInodes.dernier = NULL;
    sf->listeInodes.premier = NULL;
    return sf;
}

void DetruireSF(tSF *pSF) {
    TEST_EXISTANCE(*pSF,"DetruireSF","Tentative de free NULL",)
    DetruireSuperBloc(&((*pSF)->superBloc));

    struct sListeInodesElement *current = (*pSF)->listeInodes.premier;
    struct sListeInodesElement *temp;
    while (current != NULL) {
        temp = current->suivant;
        DetruireListeInodesElement(&current);
        current = temp;
    }

    (*pSF)->listeInodes.premier = NULL;
    free(*pSF);
    *pSF = NULL;
}

void AfficherSF(tSF sf){
    TEST_EXISTANCE(sf,"AfficherSF","Le systeme de fichier n'existe pas\n",)

    printf("sf de nom %s, super bloc :\n",sf->superBloc->nomDisque);
    AfficherSuperBloc(sf->superBloc);
    if (sf->listeInodes.nbInodes!=0){
        printf("Inodes :\n");
        struct sListeInodesElement* temp = sf->listeInodes.premier;
        for (int i = 0;i<sf->listeInodes.nbInodes;i++){
            AfficherInode(temp->inode);
            temp = temp->suivant;
        }
    }
}

static tInode AjouterInodeSF(tSF sf,natureFichier type){
    tInode inode = CreerInode(sf->listeInodes.nbInodes+1, type);
    TEST_EXISTANCE(sf, "AjouterInodeSF", "l'allocation de l'inode à loupén", NULL);
    if(sf->listeInodes.nbInodes==0){
        sf->listeInodes.premier = CreerListeInodesElement(inode);
        sf->listeInodes.dernier = sf->listeInodes.premier;
    }
    else{
        struct sListeInodesElement* avantDernier = sf->listeInodes.dernier;
        avantDernier->suivant = CreerListeInodesElement(inode);
        sf->listeInodes.dernier = avantDernier->suivant;
    }
    sf->listeInodes.dernier->suivant = NULL;
    sf->listeInodes.nbInodes++;
    return inode;
}

long Ecrire1BlocFichierSF(tSF sf, char nomFichier[], natureFichier type) {
    TEST_EXISTANCE(sf, "Ecrire1BlocFichierSF", "Le système de fichier n'existe pas\n", -1);
    FILE *fichier = fopen(nomFichier, "rb");
    TEST_EXISTANCE(fichier, "Ecrire1BlocFichierSF", "L'ouverture du fichier a échoué\n", -1);

    fseek(fichier, 0, SEEK_END);
    long taille = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);

    taille = ((taille > TAILLE_BLOC) ? TAILLE_BLOC : taille);

    tInode inode = AjouterInodeSF(sf, type);
    TEST_EXISTANCE(inode, "Ecrire1BlocFichierSF", "L'allocation de l'inode a échoué\n", -1);
    unsigned char *tampon = malloc(taille);
    TEST_EXISTANCE(tampon, "Ecrire1BlocFichierSF", "L'allocation du tampon a échoué\n", -1);

    if((long)fread(tampon, 1, taille, fichier)!=taille)
    RETOURNE_ERREUR("Ecrir1BlocFichierSF",-1,"fread a renvoyer une taille erroné\n",free(tampon);fclose(fichier);)

    fclose(fichier);
    sf->superBloc->dateDerModif = time(NULL);
    long res;
    if((res = EcrireDonneesInode1bloc(inode, tampon, taille))!=taille)
    RETOURNE_ERREUR("Ecrire1BlocFichierSF",-1,"EcireDonneesInode1bloc a renvoyer une taille erroné\n",free(tampon);)

    free(tampon);
    return res;
}


long EcrireFichierSF(tSF sf, char nomFichier[], natureFichier type){
    TEST_EXISTANCE(sf,"EcrireFichierSF","le systeme de fichier n'existe pas\n",-1)
    FILE* fichier = fopen(nomFichier,"rb");
    TEST_EXISTANCE(fichier,"EcrireFichierSF","L'ouverture du fichier à loupé",-1)

    fseek(fichier, 0, SEEK_END);
    long taille = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);

    taille = ((taille > NB_BLOCS_DIRECTS*TAILLE_BLOC) ? NB_BLOCS_DIRECTS*TAILLE_BLOC : taille);

    tInode inode = AjouterInodeSF(sf,type);
    TEST_EXISTANCE(inode, "EcrireFichierSF","l'allocation a échoué\n", -1)
    unsigned char *tampon = malloc(taille);
    TEST_EXISTANCE(tampon, "EcrireFichierSF", "L'allocation du tampon a échoué\n", -1);

    if((long)fread(tampon, 1, taille, fichier)!=taille)
    RETOURNE_ERREUR("EcrireFichierSF",-1,"fread a renvoyer une taille erroné\n",free(tampon);fclose(fichier);)

    if(EcrireDonneesInode(inode,tampon,taille,0)!=taille)
    RETOURNE_ERREUR("EcrireFichierSF",-1,"EcireDonneesInode a renvoyer une taille erroné\n",free(tampon);fclose(fichier);)

    fclose(fichier);
    free(tampon);
    sf->listeInodes.dernier->inode->type = type;
    sf->superBloc->dateDerModif = time(NULL);
    return inode->taille;
}

int SauvegarderSF(tSF sf, char nomFichier[]) {
    FILE *fichier = fopen(nomFichier, "wb");
    TEST_EXISTANCE(fichier,"SauvegarderSF","L'ouverture du fichier à loupé",-1)
    int nbInodes = sf->listeInodes.nbInodes;

    if(fwrite(&nbInodes, sizeof(int), 1, fichier) != 1)
    RETOURNE_ERREUR(SauvegarderSF,-1,"ecriture du nbInode loupé\n",)

    size_t longueur = strlen(sf->superBloc->nomDisque) + 1; // Longueur du nom du superBloc pour la relecture
    if(fwrite(&longueur, sizeof(size_t), 1, fichier) != 1)
    RETOURNE_ERREUR(SauvegarderSF,-1,"ecriture du nom du disque loupé\n",)
    if (fwrite(sf->superBloc->nomDisque, 1, longueur, fichier) != longueur)
    RETOURNE_ERREUR(SauvegarderSF,-1,"ecriture de la longueur loupé\n",)
    struct sListeInodesElement *current = sf->listeInodes.premier->suivant;

    for (int i = 0; i < nbInodes; i++) {
        if(SauvegarderInode(current->inode, fichier) != 0)
        RETOURNE_ERREUR(SauvegarderSF,-1,"échec SauvegarderInode\n",fclose(fichier);)
        current = current->suivant;
    }
    fclose(fichier);
    return 0;
}


int ChargerSF(tSF *pSF, char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "rb");
    TEST_EXISTANCE(fichier,"ChargerSF","L'ouverture du fichier à loupé",-1)
    *pSF = CreerSF("temp");
    int nbInodes;
    size_t longueure;

    if(fread(&nbInodes, sizeof(int), 1, fichier) != 1)
    RETOURNE_ERREUR(ChargerSF,-1,"echec lecture nb d'inode\n",)

    (*pSF)->listeInodes.nbInodes = nbInodes;
    if(fread(&longueure, sizeof(size_t), 1, fichier) != 1)
    RETOURNE_ERREUR(ChargerSF,-1, "echec lecture taille nom disque\n",)

    if(fread((*pSF)->superBloc->nomDisque, 1, longueure, fichier) != longueure)
    RETOURNE_ERREUR(ChargerSF,-1,"echec lecture taille nom disque\n",)

    for (int i = 0; i < nbInodes; i++) {
        tInode inode = AjouterInodeSF(*pSF, 0);
        TEST_EXISTANCE(inode, "ChargerInode","l'allocation a échoué\n", -1)
        if(ChargerInode(&inode, fichier) != 0)
        RETOURNE_ERREUR(ChargerSF,-1,"échec ChargerInode pour inode",fprintf(stderr, "%d\n", i);)
    }
    fclose(fichier);
    (*pSF)->superBloc->dateDerModif = time(NULL);
    return 0;
}
