/**
 * ProgC - Projet Automne 25-26 : Gestion de systèmes de fichiers
 * VERSION 3
 * Fichier : inode.c
 * Module de gestion des inodes.
 **/
#include "inode.h"
#include "bloc.h"

#include <stdlib.h>

#ifdef DEBUG
#define TEST_EXISTANCE(pointeur,NomFonction,MessageErreur,ValeurRetour) \
    if ((pointeur) == NULL) { \
        fprintf(stderr, "%s : %s\n", NomFonction, MessageErreur); \
        return ValeurRetour;\
    }
#else
#define TEST_EXISTANCE(pointeur,NomFonction,MessageErreur,ValeurRetour)\
    if ((pointeur) == NULL) { \
    return ValeurRetour;\
    }
#endif

#ifdef DEBUG
#define RETOURNE_ERREUR(NomFonction,ValeurRetour,MessageErreur,EtapeOptionnel){\
    fprintf(stderr, "%s : %s", #NomFonction, MessageErreur); \
    EtapeOptionnel \
    return ValeurRetour;\
    }
#else
#define RETOURNE_ERREUR(NomFonction,ValeurRetour,MessageErreur,EtapeOptionnel){\
    EtapeOptionnel \
    return ValeurRetour;\
    }
#endif

#define NB_BLOCS_DIRECTS 10

struct sInode
{
  // Numéro de l'inode
  unsigned int numero;
  // Le type du fichier : ordinaire, répertoire ou autre
  natureFichier type;
  // La taille en octets du fichier
  long taille;
  // Les adresses directes vers les blocs (NB_BLOCS_DIRECTS au maximum)
  tBloc blocDonnees[NB_BLOCS_DIRECTS];
  // Les dates : dernier accès à l'inode, dernière modification du fichier
  // et de l'inode
  time_t dateDerAcces, dateDerModif, dateDerModifInode;
};

/* V1
 * Crée et retourne un inode.
 * Entrées : numéro de l'inode et le type de fichier qui y est associé
 * Retour : l'inode créé ou NULL en cas de problème
 */

 //Retourne le bloc à l'inode (inode)
 static unsigned char** BlocDonnees(const tInode inode){
     TEST_EXISTANCE(inode,"BlocDonnees","l'inode n'existe pas",NULL)
     inode->dateDerAcces = time(NULL);
     return inode->blocDonnees;
 }

 tInode CreerInode(int numInode, natureFichier type) {
     tInode inode= malloc(sizeof(struct sInode));
     TEST_EXISTANCE(inode,"CreerInode","probleme creation\n",NULL)

     for(int i=0;i<NB_BLOCS_DIRECTS;i++) BlocDonnees(inode)[i]= NULL;
     // on initialise a NULL pour etre sur que si c'est pas changer, Detruire vera la non initialisation
     inode->numero = numInode;
     inode->type = type;
     inode->dateDerModifInode = time(NULL);

     return inode;
 }

/* V1
 * Détruit un inode.
 * Entrée : l'inode à détruire
 * Retour : aucun
 */
 void DetruireInode(tInode *pInode) {
     for (int i=0;i<NB_BLOCS_DIRECTS;i++){
         if ((*pInode)->blocDonnees[i] != NULL){
             DetruireBloc(&(*pInode)->blocDonnees[i]);
         }
     }
     free(*pInode);
     *pInode = NULL;
 }

/* V1
 * Récupère la date de dernier accès à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la date de dernier accès
 * Retour : la date de dernier accès à l'inode
 */
 time_t DateDerAcces(tInode inode) {
     TEST_EXISTANCE(inode,"DateDerAcces","l'inode n'existe pas",-1)
     inode->dateDerAcces = time(NULL);
     return inode->dateDerAcces;
 }

/* V1
 * Récupère la date de dernière modification d'un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la date de dernière modification
 * Retour : la date de dernière modification de l'inode
 */
 time_t DateDerModif(tInode inode) {
     TEST_EXISTANCE(inode,"DateDerModif","l'inode n'existe pas",-1)
     inode->dateDerAcces = time(NULL);
     return inode->dateDerModif;
 }

/* V1
 * Récupère la date de dernière modification d'u fichier associé à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la date de dernière modification du fichier associé
 * Retour : la date de dernière modification du fichier associé à l'inode
 */
 time_t DateDerModifFichier(tInode inode) {
     TEST_EXISTANCE(inode,"DateDerModifFichier","l'inode n'existe pas",-1)
     inode->dateDerAcces = time(NULL);
     return inode->dateDerModifInode;
 }

/* V1
 * Récupère le numéro d'un inode.
 * Entrée : l'inode pour lequel on souhaite connaître le numéro
 * Retour : le numéro de l'inode
 */
 unsigned int Numero(tInode inode) {
     TEST_EXISTANCE(inode,"Numero","l'inode n'existe pas",-1)
     inode->dateDerAcces = time(NULL);
     return inode->numero;
}

/* V1
 * Récupère la taille en octets du fichier associé à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître la taille
 * Retour : la taille en octets du fichier associé à l'inode
 */
 long Taille(tInode inode) {
     TEST_EXISTANCE(inode,"Taille","l'inode n'existe pas",-1)
     inode->dateDerAcces = time(NULL);
     return inode->taille;
}

/* V1
 * Récupère le type du fichier associé à un inode.
 * Entrée : l'inode pour lequel on souhaite connaître le tyep de fichier associé
 * Retour : le type du fichier associé à l'inode
 */
 natureFichier Type(tInode inode) {
     TEST_EXISTANCE(inode,"Type","l'inode n'existe pas",-1)
     inode->dateDerAcces = time(NULL);
     return inode->type;
}

static const char* stringNatureFichier(const natureFichier type){
    if(type == 0) return "ORDINAIRE";
    if(type == 1) return "REPERTOIRE";
    return "AUTRE";
}

/* V1 & V3
 * Affiche les informations d'un inode
 * Entrée : l'inode dont on souhaite afficher les informations
 * Retour : aucun
 */
 void AfficherInode(tInode inode) {
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

/* V1
 * Copie dans un inode les taille octets situés à l’adresse contenu.
 * Si taille est supérieure à la taille d’un bloc, seuls les TAILLE_BLOC premiers octets doivent être copiés.
 * Entrées : l'inode, l'adresse de la zone à recopier et sa taille en octets
 * Retour : le nombre d'octets effectivement écrits dans l'inode ou -1 en cas d'erreur
 */
 long LireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille) {
     if (inode == NULL || contenu == NULL || taille < 0)
     RETOURNE_ERREUR("LireDonneesInode1bloc",-1,"paramètres invalides\n",)
     TEST_EXISTANCE(BlocDonnees(inode)[0],"LireDonneesInode1bloc"," rien à lire\n",-1)
     //Les deux dernières lignes dans ce sens suppose qu'on assume que cela prendra moins d'une seconde a être realisé
     inode->dateDerAcces = time(NULL);
     return LireContenuBloc(BlocDonnees(inode)[0], contenu, taille);
 }

/* V1
 * Copie à l'adresse contenu les taille octets stockés dans un inode.
 * Si taille est supérieure à la taille d’un bloc, seuls les TAILLE_BLOC premiers octets doivent être copiés.
 * Entrées : l'inode, l'adresse de la zone où recopier et la taille en octets de l'inode
 * Retour : le nombre d'octets effectivement lus dans l'inode ou -1 en cas d'erreur
 */
 long EcrireDonneesInode1bloc(tInode inode, unsigned char *contenu, long taille) {
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

/* V3
 * Lit les données d'un inode avec décalage, et les stocke à une adresse donnée
 * Entrées : l'inode d'où les données sont lues, la zone où recopier ces données, la taille en octets
 * des données à lire et le décalage à appliquer (voir énoncé)
 * Sortie : le nombre d'octets effectivement lus, 0 si le décalage est au-delà de la taille
 */
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

static long ReEcrireContenuBloc(tBloc bloc,const unsigned char *contenu,const long taille,const long decallage){
    TEST_EXISTANCE(bloc,"EcrireContenuBloc","le bloc n'existe pas",-1)
    long i;
    for (i=decallage;i<taille && i<TAILLE_BLOC;i++){
        bloc[i] = contenu[i];
    }
    return i - decallage;
}

/* V3
 * Ecrit dans un inode, avec décalage, ls données stockées à une adresse donnée
 * Entrées : l'inode où écrire le contenu, l'adesse de la zone depuis laquelle lire les données, la taille en octets
 * de ces données et le décalage à appliquer (voir énoncé)
 * Sortie : le nombre d'octets effectivement écrits, ou -1 en cas d'erreur
 */
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

/* V3
 * Sauvegarde toutes les informations contenues dans un inode dans un fichier (sur disque,
 * et préalablement ouvert en écriture et en mode binaire)
 * Entrées : l'inode concerné, l'identificateur du fichier
 * Sortie : 0 en cas de succès, -1 en cas d'erreur
 */
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

/* V3
 * Charge toutes les informations d'un inode à partir d'un fichier (sur disque,
 * et préalablement ouvert en lecture et en mode binaire)
 * Entrées : l'inode concerné, l'identificateur du fichier
 * Sortie : 0 en cas de succès, -1 en cas d'erreur
 */
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
