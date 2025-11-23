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

    if (TestSauvegarderBlocAux("Projet du module ProgC", "fichier1.proj",22+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }
    if (TestSauvegarderBlocAux("", "fichier2.proj",0+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }
    if (TestSauvegarderBlocAux("AAAAA", "fichier3.proj",5+1,bloc) != 0){
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

    if (TestChargerBlocAux("Projet du module ProgC", "fichier1.proj",22+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }
    if  (TestChargerBlocAux("", "fichier2.proj",0+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }
    if (TestChargerBlocAux("AAAAA", "fichier3.proj",5+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }

    DetruireBloc(&bloc);
    return 0;
}

static int TestEcrireDonneesInodeAux(char contenu[],long taille,tInode inode,long decallage,long ecriteTaille){
    int retour;
    if ((retour = EcrireDonneesInode(inode, (unsigned char*)contenu, taille, decallage))
        != ecriteTaille-decallage){
        #ifdef DEBUG
        fprintf(stderr, "TestEcrireDonneesInodeAux : EcrireDonneesInode à loupé\n %d != %ld\n",retour,ecriteTaille);
        #endif
        AfficherInode(inode);
        DetruireInode(&inode);
        return 1;
    }
    return 0;
}

int TestEcrireDonneesInode(void){
    tInode inode = CreerInode(0, 0);

    if (TestEcrireDonneesInodeAux("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam sodales fringilla egestas. Integer vulputate ullamcorper nunc, sed varius magna fermentum at. Maecenas laoreet odio tortor, nec commodo sapien lacinia et. Cras ornare sit amet mi vitae mollis. Suspendisse potenti. Morbi non elit a velit consectetur placerat ac nec massa. Maecenas eu velit eu diam lobortis semper. Sed blandit, nisl congue finibus egestas, nisl libero porttitor libero, sed tempus nunc sapien eu elit. Integer eu ex id neque bibendum gravida ut nec nisl. Fusce non nibh vel turpis sodales aliquam ut vel ante. Pellentesque pulvinar at mi lacinia faucibus. Cras bibendum malesuada sem, at dapibus dolor ultrices a ligula."
        ,701+1,inode,0,((701+1 > NB_BLOCS_DIRECTS*TAILLE_BLOC) ? NB_BLOCS_DIRECTS*TAILLE_BLOC : 701+1))!=0){
            return 1;
    }
    DetruireInode(&inode);

    inode = CreerInode(1, 0);
    if (TestEcrireDonneesInodeAux("",0+1,inode,0,((0+1 > NB_BLOCS_DIRECTS*TAILLE_BLOC) ? NB_BLOCS_DIRECTS*TAILLE_BLOC : 0+1))!=0){
        return 1;
    }
    DetruireInode(&inode);

    inode = CreerInode(2, 0);
    if (TestEcrireDonneesInodeAux("Projet du module ProgC",0+1,inode,NB_BLOCS_DIRECTS*TAILLE_BLOC,0)!=0){
        return 1;
    }
    AfficherInode(inode);
    DetruireInode(&inode);

    inode = CreerInode(3, 0);
    if (TestEcrireDonneesInodeAux("AAAAA",5+1,inode,10,((5+1+10 > NB_BLOCS_DIRECTS*TAILLE_BLOC) ? NB_BLOCS_DIRECTS*TAILLE_BLOC : 5+1+10))!=0){
        return 1;
    }
    AfficherInode(inode);
    DetruireInode(&inode);

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
