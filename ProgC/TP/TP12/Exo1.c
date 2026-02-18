#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LGMAXNOM 30
#define LGMAXPRENOM 20
#define LGMAXMAIL 254

// Type structuré pour stocker une date de naissance
struct sDate
{
  unsigned char Jour;
  unsigned char Mois;
  unsigned short int Annee;
};

// Type structuré pour stocker un contact dans une liste simplement chaînée
struct sContact
{
  char Nom[LGMAXNOM+1];
  char Prenom[LGMAXPRENOM+1];
  char Mail[LGMAXMAIL+1];
  struct sDate Naissance;
  struct sContact *pSuivant; // Adresse du contact suivant
};

// Type structuré permettant d'accéder à une liste chaînée de contacts
struct sRepertoire
{
  struct sContact *Debut; // Adresse du premier contact de la liste
  struct sContact *Fin; // Adresse du dernier contact de la liste
};

// Type permettant de manipuler un répertoire
typedef struct sRepertoire *tRepertoire;

/* Affichage des informations d'un contact (version 1)
 * Entrée :
 *    - Contact : le contact
 */
void AfficherContact1(struct sContact Contact)
{
  printf("%s\n%s\n%s\n%02d/%02d/%d\n",
         Contact.Nom,
         Contact.Prenom,
         Contact.Mail,
         Contact.Naissance.Jour,
         Contact.Naissance.Mois,
         Contact.Naissance.Annee);
}

/* Affichage des informations d'un contact (version 2)
 * Entrée :
 *     - pContact : adresse du contact
 */
void AfficherContact2(const struct sContact *pContact)
{
    if (pContact == NULL){
        return;
    }
    printf("%s\n%s\n%s\n%02d/%02d/%d\n",
           pContact->Nom,
           pContact->Prenom,
           pContact->Mail,
           pContact->Naissance.Jour,
           pContact->Naissance.Mois,
           pContact->Naissance.Annee);
}
/* Création d'un répertoire vide
 * Valeur de retour : accès au répertoire vide alloué de manière dynamique
 */
tRepertoire CreerRepertoire(void){
    tRepertoire repertoire = malloc(sizeof(struct sRepertoire));
    if (repertoire == NULL){
        return NULL;
    }
    repertoire->Debut = NULL;
    repertoire->Fin = NULL;
    return repertoire;
}

/* Affichage de tous les contacts d'un répertoire
 * Entrée :
 *   - Repertoire : accès au répertoire
 */
void AfficherRepertoire(tRepertoire Repertoire)
{
    if (Repertoire == NULL){
        return;
    }
    struct sContact* actuel = Repertoire->Debut;
    while (actuel != NULL) {
        AfficherContact2(actuel);
        actuel = actuel->pSuivant;
    }
}

static struct sContact* copieContact(struct sContact* contact){
    struct sContact *nouveau = malloc(sizeof(struct sContact));
    if (!nouveau) return NULL;
    *nouveau = *contact;
    nouveau->pSuivant = NULL;

    return nouveau;
}

/* Ajout d'un contact à la fin d'un répertoire
 * Entrée :
 *    - pNouveau : adresse du contact à ajouter
 * Mise à jour (entrée et sortie):
 *    - Repertoire : accès au répertoire
 */
void AjouterContact(struct sContact *pNouveau, tRepertoire Repertoire){
    if (pNouveau == NULL) return;
    struct sContact* pNew = copieContact(pNouveau);
    if (Repertoire == NULL){
        Repertoire = CreerRepertoire();
        if (Repertoire == NULL) return;
    }
    if (Repertoire->Fin != NULL){
        Repertoire->Fin->pSuivant = pNew;
    }
    else {
        Repertoire->Debut= pNew;
    }
    Repertoire->Fin = pNew;
}

/* Recherche d'un contact par son nom
 * Entrées :
 *    - NomRecherche : nom recherché (chaîne de caractères)
 *    - Repertoire : accès au répertoire
 * Valeur retournée : adresse du contact trouvé ou NULL si le contact est absent
 */
struct sContact *Rechercher(char NomRecherche[], tRepertoire Repertoire)
{
    if (Repertoire == NULL)return NULL;
    struct sContact* actuel = Repertoire->Debut;
    while (actuel != NULL) {
        if(!strcmp(actuel->Nom,NomRecherche)){
            return actuel;
        }
        actuel = actuel->pSuivant;
    }
    return NULL;
}

/* Écriture de tous les contacts d'un répertoire dans un fichier au format binaire
 * Entrées :
 *    - Repertoire : accès au répertoire
 *    - NomFichier : nom du fichier (chaîne de caractères)
 */
void EcrireFichier(tRepertoire Repertoire, char NomFichier[])
{
    FILE* fichier = fopen(NomFichier,"wb");
    if(fichier==NULL){
        return;
    }
    struct sContact* actuel = Repertoire->Debut;
    while (actuel != NULL) {
        if (fwrite(actuel,sizeof(struct sContact),1,fichier)!=1){
            return;
        }
        actuel = actuel->pSuivant;
    }

    fclose(fichier);
}

void LibererRepertoire(tRepertoire *pRepertoire);

/* Lecture d'un répertoire dans un fichier au format binaire
 * Entrée :
 *    - NomFichier : nom du fichier (chaîne de caractères)
 * Valeur de retour : accès au répertoire créé ou NULL en cas de problème
 */
tRepertoire LireFichier(const char NomFichier[])
{
     tRepertoire rep = CreerRepertoire();
     if (rep == NULL) return NULL;

     FILE *fichier = fopen(NomFichier, "rb");
     if (fichier == NULL) {
         free(rep);
         return NULL;
     }

     struct sContact temp;
     while (fread(&temp, sizeof(struct sContact), 1, fichier) == 1) {
         struct sContact *nouveau = copieContact(&temp);
         if (nouveau == NULL) {
             fclose(fichier);
             LibererRepertoire(&rep);
             return NULL;
         }
         AjouterContact(nouveau, rep);
         free(nouveau);
     }
     fclose(fichier);
     return rep;
 }



/* Libération de tout l'espace mémoire occupé par un répertoire
 * et mise à NULL de l'accès au répertoire
 * Mise à jour (entrée et sortie) :
 *    - pRepertoire : adresse de l'accès à un répertoire
 */
void LibererRepertoire(tRepertoire *pRepertoire){
    if (pRepertoire == NULL || *pRepertoire == NULL)return;
    struct sContact* actuel = (*pRepertoire)->Debut;
    struct sContact* temp = actuel;
    while (actuel != NULL) {
        temp = actuel->pSuivant;
        free(actuel);
        actuel = temp;
    }
    free(*pRepertoire);
    *pRepertoire = NULL;
}


int main(void)
{
  // Trois contacts
  struct sContact
    c1={"KARENA","Emma","emma.karena@legria.es",{1,5,2001},NULL},
    c2={"DEUF","John","john.deuf@mayonnaise.fr",{12,1,1999},NULL},
    c3={"MANVUSSA","Gerard","gerard.manvussa@etonnant.com",{24,11,2000},NULL};

  printf("***** Création du répertoire.\n");
  tRepertoire Rep=CreerRepertoire();

  printf("***** Ajout de trois contacts.\n");
  AjouterContact(&c1,Rep);
  AjouterContact(&c2,Rep);
  AjouterContact(&c3,Rep);
  printf("***** Répertoire initial :\n");
  AfficherRepertoire(Rep);

  // Contact supplémentaire
  struct sContact Nouv={"AMBOLAGE",
                        "Oscar",
                        "oscar.ambolage@latele.com",
                        {9,6,2002},
                        NULL};
  printf("***** Ajout d'un contact.\n");
  AjouterContact(&Nouv,Rep);
  printf("***** Répertoire après ajout :\n");
  AfficherRepertoire(Rep);

  char Nom[]="DEUF"; // Nom qui va être recherché
  printf("\n***** Recherche de %s :\n",Nom);
  struct sContact *Res=Rechercher(Nom,Rep);
  if (Res==NULL)
    printf("%s n'est pas dans le repertoire.\n",Nom);
  else
    AfficherContact2(Res);

  char Fichier[]="repertoire2.dat"; // Nom du fichier binaire
  printf("\n***** Écriture du répertoire dans le fichier %s.\n",Fichier);
  EcrireFichier(Rep,Fichier);
  printf("\n***** Lecture du répertoire depuis le fichier %s.\n",Fichier);
  tRepertoire RepLu=LireFichier("repertoire2.dat");
  printf("***** Répertoire lu :\n");
 AfficherRepertoire(RepLu);

  printf("\n***** Libération des répertoires.\n");
  LibererRepertoire(&Rep);
  LibererRepertoire(&RepLu);

  return 0;
}
