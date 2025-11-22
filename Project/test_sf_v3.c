#include "test_sf_v3.h"
#include "inode.h"
#include <stdio.h>
#include <string.h>

static int TestSauvegarderBlocAux(char string[],char nomFichier[], int taille, tBloc bloc){
    char chemin[256];
    sprintf(chemin, "%s/%s", CHEMIN_ACCES, nomFichier);

    FILE* fichier = fopen(chemin,"w");
    if (fichier == NULL){
        #ifdef DEBUG
        fprintf(stderr, "TestSauvegarderBloc : L'ouverture du fichier à loupé\n");
        #endif
        return 1;
    }
    long retour;
    retour = EcrireContenuBloc(bloc,(unsigned char*) string, taille);
    if (retour != taille){
        #ifdef DEBUG
        fprintf(stderr, "TestSauvegarderBloc : EcrireContenuBloc à loupé\n");
        #endif
        return 1;
    }

    if (SauvegarderBloc(bloc, 23+1,fichier) != 0){
        return 1;
    }
    fclose(fichier);
    return 0;
}

int TestSauvegarderBloc(void){
    tBloc bloc = CreerBloc();

    if (TestSauvegarderBlocAux("Projet du module ProgC", "fichier1.proj",23+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }
    if (TestSauvegarderBlocAux("Projet du module ProgC", "fichier2.proj",0+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }
    if (TestSauvegarderBlocAux("Projet du module ProgC", "fichier3.proj",5+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }

    DetruireBloc(&bloc);
    return 0;
}

static int TestChargerBlocAux(char string[],char nomFichier[], int taille, tBloc bloc){
    char chemin[256];
    sprintf(chemin, "%s/%s", CHEMIN_ACCES, nomFichier);

    FILE* fichier = fopen(chemin,"r");
    if (fichier == NULL){
        #ifdef DEBUG
        fprintf(stderr, "TestChargerBloc : L'ouverture du fichier à loupé\n");
        #endif
        return 1;
    }

    unsigned char contenu[100];
    if (ChargerBloc(bloc,taille,fichier)== -1) return -1;

    LireContenuBloc(bloc,contenu,taille);
    int retour = strcmp((char *) contenu,(char*)string);
    if (retour != 0){
        #ifdef DEBUG
        fprintf(stderr, "TestLireContenuBloc : [%s] et [%s] sont different\n",(char *) bloc,(char*)string);
        #endif
        return 1;
    }

    fclose(fichier);
    return 0;
}

int TestChargerBloc(void){
    tBloc bloc = CreerBloc();

    if (TestChargerBlocAux("Projet du module ProgC", "fichier1.proj",23+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }
    if  (TestChargerBlocAux("Projet du module ProgC", "fichier2.proj",0+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }
    if (TestChargerBlocAux("Projet du module ProgC", "fichier3.proj",5+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }
    return 0;
}

int TestEcrireDonneesInode(void){
    return 0;
}

int TestLireDonneesInode(void){
    return 0;
}

int TestSauvegarderInode(void){
    return 0;
}

int TestChargerInode(void){
    return 0;
}

int TestEcrireFichierSF(void){
    return 0;
}

int TestSauvegarderSF(void){
    return 0;
}

int TestChargerSF(void){
    return 0;
}
