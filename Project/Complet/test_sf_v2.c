#include "inode.h"
#include "sf.h"
#include "standard.h"
#include <stdio.h>

#include "test_sf_v2.h"

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
    unsigned char ch1[TAILLE_BLOC];
    if ((valRetour = LireDonneesInode1bloc(sf->listeInodes.dernier->inode,ch1,taille))!=taille){
        #ifdef DEBUG
        fprintf(stderr, "TestEcrire1BlocFichierSFAux : LireDonnesInode à loupé, [%d], [%d]\n",valRetour,taille);
        #endif
        return 1;
    }
    if (ReStrcmp((char*) ch1,chaine,taille)!=0){
        #ifdef DEBUG
        fprintf(stderr, "TestEcrire1BlocFichierSFAux : les chaines sont differentes\n");
        #endif
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
