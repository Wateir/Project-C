#include <stdio.h>
#include <stdlib.h>
#ifdef DEBUG
#include <string.h>
#endif
#include <time.h>
#include "inode.h"
#include "macro.h"

#define STRING_ENUM (12+1)

tBloc CreerBloc(void){
    tBloc bloc = calloc(TAILLE_BLOC,sizeof(unsigned char));
    TEST_EXISTANCE(bloc,"CreerBloc","probleme creation \n",NULL)
    return bloc;
}

void DetruireBloc(tBloc *pBloc){
    free(*pBloc);
    *pBloc = NULL;
}

long EcrireContenuBloc(tBloc bloc, unsigned char *contenu, long taille){
    TEST_EXISTANCE(bloc,"EcrireContenuBloc","le bloc n'existe pas",-1)
    int i;
    for (i=0;i<taille && i<TAILLE_BLOC;i++){
        bloc[i] = contenu[i];
    }
    return (long) i;
}

//Reimplementation de EcrireContenuBloc permetant un decallage
static long ReEcrireContenuBloc(tBloc bloc,const unsigned char *contenu,const long taille,const long decallage){
    TEST_EXISTANCE(bloc,"EcrireContenuBloc","le bloc n'existe pas",-1)
    long i;
    for (i=decallage;i<taille && i<TAILLE_BLOC;i++){
        bloc[i] = contenu[i];
    }
    return i - decallage;
}

long LireContenuBloc(tBloc bloc, unsigned char *contenu, long taille){
    TEST_EXISTANCE(bloc,"LireContenuBloc","le bloc n'existe pas",-1)
    int i;
    for (i=0;i < taille && i < TAILLE_BLOC;i++){
        contenu[i] = bloc[i];
    }
    return (long) i;
}

int SauvegarderBloc(tBloc bloc, long taille, FILE *fichier){
    TEST_EXISTANCE(fichier,"SauvegarderBloc","le fichier n'existe pas",-1)
    TEST_EXISTANCE(bloc,"SauvegarderBloc","le bloc n'existe pas",-1)
    if (taille>TAILLE_BLOC)
    RETOURNE_ERREUR("SauvegarderBloc",-1,"taille obtenu trop importante",)

    int valRetour = fwrite(bloc, 1, taille, fichier);
    if (valRetour != taille)
    RETOURNE_ERREUR("SauvegarderBloc",-1,"écriture échouée ",fprintf(stderr,"(%d/%zu octets)\n",valRetour, taille);)
    return 0;
}

int ChargerBloc(tBloc bloc, long taille, FILE *fichier){
    TEST_EXISTANCE(fichier, "ChargerBloc", "le fichier n'existe pas", -1)
    TEST_EXISTANCE(bloc,   "ChargerBloc", "le bloc n'existe pas",   -1)
    if (taille>TAILLE_BLOC)
    RETOURNE_ERREUR("ChargerBloc",-1,"taille obtenu trop importante",)


    int valRetour = fread(bloc, 1, taille, fichier);
    if (valRetour != taille)
    RETOURNE_ERREUR("ChargerBloc",-1,"lecture échouée ",fprintf(stderr,"(%d/%zu octets)\n",valRetour, taille);)
    return 0;
}


//Retourne le bloc à l'inode (inode)
static unsigned char** BlocDonnees(const tInode inode){
    TEST_EXISTANCE(inode,"BlocDonnees","l'inode n'existe pas",NULL)
    inode->dateDerAcces = time(NULL);
    return inode->blocDonnees;
}

tInode CreerInode(unsigned int numInode, natureFichier type){
    tInode inode= malloc(sizeof(struct sInode));
    TEST_EXISTANCE(inode,"CreerInode","probleme creation\n",NULL)

    for(int i=0;i<NB_BLOCS_DIRECTS;i++) BlocDonnees(inode)[i]= NULL;
    // on initialise a NULL pour etre sur que si c'est pas changer, Detruire vera la non initialisation
    inode->numero = numInode;
    inode->type = type;
    inode->dateDerModifInode = time(NULL);

    return inode;
}

void DetruireInode(tInode* pInode){
    for (int i=0;i<NB_BLOCS_DIRECTS;i++){
        if ((*pInode)->blocDonnees[i] != NULL){
            DetruireBloc(&(*pInode)->blocDonnees[i]);
        }
    }
    free(*pInode);
    *pInode = NULL;
}

unsigned int Numero(tInode inode){
    TEST_EXISTANCE(inode,"Numero","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->numero;
}

time_t DateDerAcces(tInode inode){
    TEST_EXISTANCE(inode,"DateDerAcces","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->dateDerAcces;
}

time_t DateDerModif(tInode inode){
    TEST_EXISTANCE(inode,"DateDerModif","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->dateDerModif;
}

time_t DateDerModifFichier(tInode inode){
    TEST_EXISTANCE(inode,"DateDerModifFichier","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->dateDerModifInode;
}

natureFichier Type(tInode inode){
    TEST_EXISTANCE(inode,"Type","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->type;
}


long Taille(tInode inode){
    TEST_EXISTANCE(inode,"Taille","l'inode n'existe pas",-1)
    inode->dateDerAcces = time(NULL);
    return inode->taille;
}

//Retourne le string associé au type (type)
static const char* stringNatureFichier(const natureFichier type){
    if(type == 0) return "ORDINAIRE";
    if(type == 1) return "REPERTOIRE";
    return "AUTRE";
}

void AfficherInode(tInode inode){
    TEST_EXISTANCE(inode,"AfficherInode","L'inode n'existe pas \n",)
    TEST_EXISTANCE(BlocDonnees(inode)[0],"AfficherInode","inode->blocDonnees[0] est vide",)
    if (Taille(inode)<0)
    RETOURNE_ERREUR("AfficherInode",,"taille negative\n",printf("vide\n");)

    printf("-----Inode-----[%d]\n",Numero(inode));
    printf("type : %s\n",stringNatureFichier(Type(inode)));
    printf("\ttaille : %ld octets\n",Taille(inode));

    time_t date = DateDerAcces(inode);
    printf("\tdate dernier accès : %s",ctime(&date));
    date = DateDerModif(inode);
    printf("\tdate derniere modification : %s",ctime(&date));
    date = DateDerModifFichier(inode);
    printf("\tdate dernier modification inode : %s",ctime(&date));

    long resteALire = Taille(inode);
    for (int i = 0; i < NB_BLOCS_DIRECTS; i++) {
        if (BlocDonnees(inode)[i] != NULL) {
            for (int j = 0; j < TAILLE_BLOC && resteALire > 0; j++) {
                putchar(BlocDonnees(inode)[i][j]);
                resteALire--;
            }
        }
    }
    printf("\n");

    inode->dateDerAcces = time(NULL);
}

long EcrireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille){
    if (inode == NULL || contenu == NULL || taille < 0)
    RETOURNE_ERREUR("EcrireDonneesInode1bloc",-1,"paramètres invalides\n",)

    if (BlocDonnees(inode)[0]==NULL){
        BlocDonnees(inode)[0] = CreerBloc();
        if (BlocDonnees(inode)[0]==NULL)
        RETOURNE_ERREUR("EcrireDonneesInode1bloc",-1,"allocation à loupé\n",)
    }
    inode->taille = taille = EcrireContenuBloc(BlocDonnees(inode)[0], contenu, taille);
    BlocDonnees(inode)[1] = NULL;
    inode->dateDerAcces = time(NULL);
    inode->dateDerModif = time(NULL);
    return Taille(inode);

}

long LireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille){
    if (inode == NULL || contenu == NULL || taille < 0)
    RETOURNE_ERREUR("LireDonneesInode1bloc",-1,"paramètres invalides\n",)
    TEST_EXISTANCE(BlocDonnees(inode)[0],"LireDonneesInode1bloc"," rien à lire\n",-1)
    //Les deux dernières lignes dans ce sens suppose qu'on assume que cela prendra moins d'une seconde a être realisé
    inode->dateDerAcces = time(NULL);
    return LireContenuBloc(BlocDonnees(inode)[0], contenu, taille);
}

long EcrireDonneesInode(tInode inode, unsigned char *contenu, long taille, long decalage) {
    if (inode == NULL || contenu == NULL || taille < 0)
    RETOURNE_ERREUR("EcrireDonneesInode",-1,"paramètres invalides\n",)
    long resteEcrire = taille;
    long iDecalage = decalage;
    int i = iDecalage / TAILLE_BLOC;
    long posDansBloc = iDecalage % TAILLE_BLOC;

    while (i < NB_BLOCS_DIRECTS && resteEcrire > 0) {
        if (BlocDonnees(inode)[i] == NULL) {
            inode->blocDonnees[i] = CreerBloc();
            TEST_EXISTANCE(BlocDonnees(inode)[i],"EcrireDonneesInode","échec allocation bloc\n",(inode->taille = taille - resteEcrire))
        }
        long espaceBloc = TAILLE_BLOC - posDansBloc;
        long aEcrire;
        if (resteEcrire < espaceBloc) {
            aEcrire = resteEcrire;
        } else {
            aEcrire = espaceBloc;
        }

        long ecrit = ReEcrireContenuBloc(inode->blocDonnees[i],contenu+ (taille- resteEcrire), aEcrire,posDansBloc);
        if (ecrit < 0) return (inode->taille = taille - resteEcrire);
        resteEcrire -= ecrit;
        posDansBloc = 0;
        i++;
    }

    inode->dateDerModif = time(NULL);
    inode->dateDerAcces = time(NULL);
    return (inode->taille = taille - resteEcrire);
}

long LireDonneesInode(tInode inode, unsigned char *contenu, long taille, long decalage){
    if (inode == NULL || contenu == NULL || taille < 0)
    RETOURNE_ERREUR("LireDonneesInode",-1,"paramètres invalides\n",)
    long ecris = 0;
    long iDecalage = decalage;
    for (int i=0;ecris<taille && i<NB_BLOCS_DIRECTS;i++){
        for(int j =0;j < TAILLE_BLOC && ecris < taille;j++){
            TEST_EXISTANCE(BlocDonnees(inode)[i],"LireDonneesInode","Bloc non initialisé\n",ecris)
            if(iDecalage>0)iDecalage--;
            else{
                contenu[ecris] = BlocDonnees(inode)[i][j];
                ecris++;
            }
        }
    }
    inode->dateDerAcces = time(NULL);
    return ecris;
}

int SauvegarderInode(tInode inode, FILE *fichier) {
    TEST_EXISTANCE(fichier,"SauvegarderInode","le fichier n'existe pas", -1)
    TEST_EXISTANCE(inode,"SauvegarderInode","l'inode n'existe pas",   -1)

    long numero = Numero(inode), type   = Type(inode), taille = Taille(inode);

    if (fwrite(&numero, sizeof(long), 1, fichier) != 1)
    RETOURNE_ERREUR("SauvegarderInode",-1,"ecriture du numero loupé\n",)
    if (fwrite(&type, sizeof(long), 1, fichier) != 1)
    RETOURNE_ERREUR("SauvegarderInode",-1,"ecriture du type loupé\n",)
    if (fwrite(&taille, sizeof(long), 1, fichier) != 1)
    RETOURNE_ERREUR("SauvegarderInode",-1,"ecriture de la taille loupé\n",)

    unsigned char *contenu = malloc(taille);
    TEST_EXISTANCE(contenu, "SauvegarderInode","l'allocation a échoué\n", -1)
    if (LireDonneesInode(inode, contenu, taille, 0) != taille)
    RETOURNE_ERREUR("SauvegarderInode",-1,"lecture données incomplète\n",free(contenu);)
    if (fwrite(contenu, 1, taille, fichier) != (size_t)taille)
    RETOURNE_ERREUR("SauvegarderInode",-1,"ecriture des données à loupé\n",free(contenu);)
    free(contenu);
    return 0;
}


int ChargerInode(tInode *pInode, FILE *fichier) {
    TEST_EXISTANCE(fichier,"ChargerInode","le fichier n'existe pas", -1)
    TEST_EXISTANCE(pInode,"ChargerInode","l'inode n'existe pas",   -1)

    long numero, type, taille;
    if (fread(&numero, sizeof(long), 1, fichier) != 1)
    RETOURNE_ERREUR("ChargerInode",-1,"lecture du numero loupé\n",)
    if (fread(&type, sizeof(long), 1, fichier) != 1)
    RETOURNE_ERREUR("ChargerInode",-1,"lecture du type loupé\n",)
    if (fread(&taille, sizeof(long), 1, fichier) != 1)
    RETOURNE_ERREUR("ChargerInode",-1,"lecture de la taille loupé\n",)

    (*pInode)->numero = numero;
    (*pInode)->type   = type;
    (*pInode)->taille = taille;
    unsigned char *contenu = malloc(taille);
    TEST_EXISTANCE(contenu, "ChargerInode","l'allocation a échoué\n", -1)

    if (fread(contenu, 1, taille, fichier) != (size_t)taille)
    RETOURNE_ERREUR("ChargerInode",-1,"erreur de lecture du contenu\n",)

    if (EcrireDonneesInode(*pInode, contenu, taille, 0) != taille)
    RETOURNE_ERREUR("ChargerInode",-1,"écriture interne incomplète\n",)

    free(contenu);
    return 0;
}
