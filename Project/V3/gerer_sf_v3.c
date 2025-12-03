#include "sf.h"
#include "inode.h"
#include "bloc.h"
#include <stdio.h>

#define CHEMIN_ACCES "./"
#define TAILLE_CHEMIN 256

#ifndef DEBUG
#define TEST(NomFonctionTest,ParametreFonction,TypeDebug) \
    if (NomFonctionTest(ParametreFonction)){ \
        fprintf(stderr, "%s à loupé, make %s à peut-être plus d'information\n",#NomFonctionTest,TypeDebug);\
        return 1;}
#else
#define TEST(NomFonctionTest,ParametreFonction,TypeDebug) if (NomFonctionTest(ParametreFonction))return 1;
#endif

static int TestSauvegarderBlocAux(char string[],char nomFichier[], int taille, tBloc bloc){
    char chemin[TAILLE_CHEMIN];
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

static int TestChargerBlocAux(char nomFichier[], int taille, tBloc bloc){
    char chemin[TAILLE_CHEMIN];
    sprintf(chemin, "%s/%s", CHEMIN_ACCES, nomFichier);

    FILE* fichier = fopen(chemin,"r");
    if (fichier == NULL){
        #ifdef DEBUG
        fprintf(stderr, "TestChargerBloc : L'ouverture du fichier [%s] à loupé\n",chemin);
        #endif
        return 1;
    }

    unsigned char contenu[TAILLE_BLOC+1];
    if (ChargerBloc(bloc,taille,fichier)== -1) return -1;

    LireContenuBloc(bloc,contenu,taille);
    fclose(fichier);
    return 0;
}

int TestChargerBloc(void){
    tBloc bloc = CreerBloc();

    if (TestChargerBlocAux("fichier1.proj",22+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }
    if  (TestChargerBlocAux("fichier2.proj",0+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }
    if (TestChargerBlocAux("fichier3.proj",5+1,bloc) != 0){
        DetruireBloc(&bloc);
        return 1;
    }

    DetruireBloc(&bloc);
    return 0;
}

static int TestEcrireDonneesInodeAux(char contenu[],long taille,tInode inode,long decallage,long ecriteTaille){
    int retour;
    if ((retour = EcrireDonneesInode(inode, (unsigned char*)contenu, taille, decallage))
        != ecriteTaille){
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
        ,701+1,inode,0,640)!=0){
            return 1;
    }
    DetruireInode(&inode);

    inode = CreerInode(1, 0);
    if (TestEcrireDonneesInodeAux("",0+1,inode,0,0+1 )!=0){
        return 1;
    }
    DetruireInode(&inode);

    inode = CreerInode(2, 0);
    if (TestEcrireDonneesInodeAux("Projet du module ProgC",22+1,inode,640,0)!=0){
        return 1;
    }
    AfficherInode(inode);
    DetruireInode(&inode);

    inode = CreerInode(3, 0);
    if (TestEcrireDonneesInodeAux("AAAAA",5+1,inode,10,5+1)!=0){
        return 1;
    }
    AfficherInode(inode);
    DetruireInode(&inode);

    return 0;
}

int TestLireDonneesInode(void){
    tInode inode = CreerInode(0, 0);
    if (LireDonneesInode(inode, NULL, 23+1,0) != -1){
        fprintf(stderr, "TestLireDonneesInode : Retourne pas -1 avec contenu NULL\n");
        DetruireInode(&inode);
        return 1;
    }
    EcrireDonneesInode(inode,(unsigned char *) "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam sodales fringilla egestas. Integer vulputate ullamcorper nunc, sed varius magna fermentum at. Maecenas laoreet odio tortor, nec commodo sapien lacinia et. Cras ornare sit amet mi vitae mollis. Suspendisse potenti. Morbi non elit a velit consectetur placerat ac nec massa. Maecenas eu velit eu diam lobortis semper. Sed blandit, nisl congue finibus egestas, nisl libero porttitor libero, sed tempus nunc sapien eu elit. Integer eu ex id neque bibendum gravida ut nec nisl. Fusce non nibh vel turpis sodales aliquam ut vel ante. Pellentesque pulvinar at mi lacinia faucibus. Cras bibendum malesuada sem, at dapibus dolor ultrices a ligula."
        , 701+1,0);
    unsigned char contenu[640];
    if (LireDonneesInode(inode,contenu,701+1 ,0) != 640){
        DetruireInode(&inode);
        return 1;
    }
    DetruireInode(&inode);
    return 0;

}

int TestSauvegarderInode(void){
    char chemin[TAILLE_CHEMIN];
    sprintf(chemin, "%s/%s", CHEMIN_ACCES, "fichier4.proj");
    FILE* fichier = fopen(chemin,"w");
    if (fichier == NULL){
        #ifdef DEBUG
        fprintf(stderr, "TestSauvegarderInode : L'ouverture du fichier à loupé\n");
        #endif
        return 1;
    }
    tInode inode = CreerInode(2, 2);
    EcrireDonneesInode(inode,(unsigned char *) "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam sodales fringilla egestas. Integer vulputate ullamcorper nunc, sed varius magna fermentum at. Maecenas laoreet odio tortor, nec commodo sapien lacinia et. Cras ornare sit amet mi vitae mollis. Suspendisse potenti. Morbi non elit a velit consectetur placerat ac nec massa. Maecenas eu velit eu diam lobortis semper. Sed blandit, nisl congue finibus egestas, nisl libero porttitor libero, sed tempus nunc sapien eu elit. Integer eu ex id neque bibendum gravida ut nec nisl. Fusce non nibh vel turpis sodales aliquam ut vel ante. Pellentesque pulvinar at mi lacinia faucibus. Cras bibendum malesuada sem, at dapibus dolor ultrices a ligula."
        , 701+1,0);


    if (SauvegarderInode(inode,fichier) != 0){
        fclose(fichier);
        DetruireInode(&inode);
        return 1;
    }

    fclose(fichier);
    DetruireInode(&inode);
    return 0;
}

int TestChargerInode(void){
    char chemin[TAILLE_CHEMIN];
    sprintf(chemin, "%s/%s", CHEMIN_ACCES, "fichier4.proj");
    FILE* fichier = fopen(chemin,"r");
    if (fichier == NULL){
        #ifdef DEBUG
        fprintf(stderr, "TestChargerInode : L'ouverture du fichier à loupé\n");
        #endif
        fclose(fichier);
        return 1;
    }
    if (ChargerInode(NULL,fichier)==0){
        #ifdef DEBUG
        fprintf(stderr, "TestChargerInode : inode = NULL ne retourne pas une erreur\n");
        #endif
        fclose(fichier);
        return 1;
    }
    tInode inode = CreerInode(2, 2);
    if (ChargerInode(&inode,fichier)!=0){
        DetruireInode(&inode);
        fclose(fichier);
        return 1;
    }

    DetruireInode(&inode);
    fclose(fichier);
    return 0;
}

static int TestEcrireFichierSFAux(char nomFichier[],int taille,char chaine[],tSF sf,natureFichier type){
    char chemin[TAILLE_CHEMIN];
    sprintf(chemin, "%s/%s", CHEMIN_ACCES,nomFichier);
    FILE* fichier = fopen(chemin,"w");
    if (fichier == NULL){
        #ifdef DEBUG
        fprintf(stderr, "TestEcrireFichierSFAux : L'ouverture du fichier à loupé\n");
        #endif
        return 1;
    }
    int valRetour = fwrite(chaine,sizeof(char),taille, fichier);
    if (valRetour!= taille){
        #ifdef DEBUG
        fprintf(stderr, "TestEcrireFichierSFAux : EcrireContenuBloc à loupé\n");
        #endif
        return 1;
    }
    fclose(fichier);
    if (EcrireFichierSF(sf,chemin,type) != taille){
        #ifdef DEBUG
        fprintf(stderr, "TestEcrireFichierSFAux :taille differente\n");
        #endif
        return 1;
    }
    return 0;
}

int TestEcrireFichierSF(void){
    tSF sf = CreerSF("nvme0n1p2");

    if (TestEcrireFichierSFAux("fichier8.proj",22+1,"Projet du module ProgC",sf,2)!=0){
        DetruireSF(&sf);
        return 1;
    }
    if (TestEcrireFichierSFAux("fichier9.proj",0+1,"",sf,1)!=0){
        DetruireSF(&sf);
        return 1;
    }
    if (TestEcrireFichierSFAux("fichier10.proj",5+1,"AAAAA",sf,3)!=0){
        DetruireSF(&sf);
        return 1;
    }
    if (TestEcrireFichierSFAux("fichier11.proj",640,"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam sodales fringilla egestas. Integer vulputate ullamcorper nunc, sed varius magna fermentum at. Maecenas laoreet odio tortor, nec commodo sapien lacinia et. Cras ornare sit amet mi vitae mollis. Suspendisse potenti. Morbi non elit a velit consectetur placerat ac nec massa. Maecenas eu velit eu diam lobortis semper. Sed blandit, nisl congue finibus egestas, nisl libero porttitor libero, sed tempus nunc sapien eu elit. Integer eu ex id neque bibendum gravida ut nec nisl. Fusce non nibh vel turpis sodales aliquam ut vel ante. Pellentesque pulvinar at mi lacinia faucibus. Cras bibendum malesuada sem, at dapibus dolor ultrices a ligula.",sf,3)!=0){
        DetruireSF(&sf);
        return 1;
    }
    DetruireSF(&sf);
    return 0;
}

int TestSauvegarderSF(void){
    return 0;
}

int TestChargerSF(void){
    return 0;
}

int main(void){
    printf("Lancement de La batterie de test ....\n");


    TEST(TestSauvegarderBloc,,"debug");
    TEST(TestChargerBloc,,"debug");

    TEST(TestEcrireDonneesInode,,"debug");
    TEST(TestLireDonneesInode,,"debug");
    TEST(TestSauvegarderInode,,"debug");
    TEST(TestChargerInode,,"debug");

    TEST(TestEcrireFichierSF,,"debug");
    TEST(TestSauvegarderSF,,"debug");
    TEST(TestChargerSF,,"debug");

    printf("Tout les tests sont passé avec succes ....\n");
    return 0;
}
