#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LGMAXNOM 30
#define LGMAXPRENOM 20
#define LGMAXMAIL 254
#define LGMAXREP 64

// Type structuré pour stocker une date de naissance
struct sDate
{
  unsigned char Jour;
  unsigned char Mois;
  unsigned short int Annee;
};

// Type structuré pour stocker un contact
struct sContact
{
  char Nom[LGMAXNOM+1];
  char Prenom[LGMAXPRENOM+1];
  char Mail[LGMAXMAIL+1];
  struct sDate Naissance;
};


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
  // Remarque : %02d signifie entier sur 2 caractères avec ajout éventuel d'un 0 à gauche
}

/* Affichage des informations d'un contact (version 2)
 * Entrée :
 *     - pContact : adresse du contact
 */
void AfficherContact2(const struct sContact *pContact)
{
    printf("%s\n%s\n%s\n%02d/%02d/%d\n",
           pContact->Nom,
           pContact->Prenom,
           pContact->Mail,
           pContact->Naissance.Jour,
           pContact->Naissance.Mois,
           pContact->Naissance.Annee);
}

/* Affichage de tous les contacts d'un répertoire
 * Entrées :
 *   - Repertoire : tableau de contacts
 *   - NbContacts : nombre de contacts
 */
void AfficherRepertoire(struct sContact Repertoire[], int NbContacts)
{
  for(int i=0;i<NbContacts;i++){
      AfficherContact2(&Repertoire[i]);
  }
}

/* Ajout d'un contact à la fin d'un répertoire
 * Entrée :
 *    - pNouveau : adresse du contact à ajouter
 * Mises à jour (entrées et sorties):
 *    - Repertoire : tableau de contacts
 *    - pNbContact : adresse du nombre de contacts
 */
void AjouterContact(struct sContact *pNouveau,
                    struct sContact Repertoire[], int *pNbContacts)
{
    Repertoire[*pNbContacts] = *pNouveau;
    (*pNbContacts)++;
}

/* Recherche d'un contact par son nom
 * Entrées :
 *    - NomRecherche : nom recherché (chaîne de caractères)
 *    - Repertoire : tableau de contacts
 *    - NbContacts : nombre de contacts
 * Valeur retournée : indice du contact dans le tableau ou -1 si le contact est
 * absent
 */
int Rechercher(char NomRecherche[], struct sContact Repertoire[],
               int NbContacts)
{
  for(int i=0;i<NbContacts;i++){
      if(!strcmp(Repertoire[i].Nom,NomRecherche)){
          return i;
      }
  }
  return -1;
}

/* Écriture de tous les contacts d'un répertoire dans un fichier au format binaire
 * Entrées :
 *    - Repertoire : tableau de contacts
 *    - NbContacts : nombre de contacts
 *    - NomFichier : nom du fichier (chaîne de caractères)
 */
void EcrireFichier(struct sContact Repertoire[], int NbContacts,
                   char NomFichier[])
{
    FILE* fichier = fopen(NomFichier,"wb");
    if(fichier==NULL){
        return;
    }
    if (fwrite(&NbContacts,sizeof(int),1,fichier)!=1){
        return;
    }
    for(int i =0;i<NbContacts;i++){
        if (fwrite(&Repertoire[i],sizeof(struct sContact),1,fichier)!=1){
            return;
        }
    }
    fclose(fichier);
}

/* Lecture d'un répertoire dans un fichier au format binaire
 * Version 1 : lecture contact par contact
 * Entrée :
 *    - NomFichier : nom du fichier (chaîne de caractères)
 * Sortie :
 *    - Repertoire : tableau de contacts
 * Valeur de retour : nombre de contacts lus
 */
int LireFichier1(struct sContact Repertoire[], char NomFichier[])
{
    FILE* fichier = fopen(NomFichier,"rb");
    if(fichier==NULL){
        return -1;
    }
    int NbContacts;
    if (fread(&NbContacts,sizeof(int),1,fichier)!=1){
        return -1;
    }
    for(int i =0;i<NbContacts;i++){
        if (fread(&Repertoire[i],sizeof(struct sContact),1,fichier)!=1){
            return -1;
        }
    }
    fclose(fichier);
    return NbContacts;
}

/* Lecture d'un répertoire dans un fichier au format binaire
 * Version 2 : une seule lecture de tous les contacts après calcul du nombre de
 * contacts
 * Entrée :
 *    - NomFichier : nom du fichier (chaîne de caractères)
 * Sortie :
 *    - Repertoire : tableau de contacts
 * Valeur de retour : nombre de contacts lus
 */
int LireFichier2(struct sContact Repertoire[], char NomFichier[])
{
    FILE* fichier = fopen(NomFichier,"rb");
    if(fichier==NULL){
        return -1;
    }
    int NbContacts;
    if (fread(&NbContacts,sizeof(int),1,fichier)!=1){
        return -1;
    }
    if (fread(Repertoire,sizeof(struct sContact),NbContacts,fichier)!=(size_t)NbContacts){
        return -1;
    }
    fclose(fichier);
    return NbContacts;
}

/* Fonction de comparaison de deux contacts pour le tri d'un tableau de contact
 * par ordre lexicographique, croissant des noms
 * Entrées :
 *    - pc1 : adresse du premier contact
 *    - pc2 : adresse du second contact
 * Valeur de retour : entier supérieur, égal ou inférieur à 0, selon que le nom
 * du premier contact est supérieur, égal ou inférieur au nom du second contact
 */
int CompareContacts(const void *pc1, const void *pc2)
{
    struct sContact* Pc1 = (struct sContact*) pc1;
    struct sContact* Pc2 = (struct sContact*) pc2;
    return strcmp(Pc1->Nom, Pc2->Nom);
}


int main(void)
{
  // Répertoire initialisé avec trois contacts
  struct sContact Rep[LGMAXREP]=
    {{"KARENA","Emma","emma.karena@legria.es",{1,5,2001}},
     {"DEUF","John","john.deuf@mayonnaise.fr",{12,1,1999}},
     {"MANVUSSA","Gerard","gerard.manvussa@etonnant.com",{24,11,2000}}
    };
  int NbContacts=3;

  printf("***** Répertoire initial :\n");
  AfficherRepertoire(Rep,NbContacts);

  // Contact supplémentaire
  struct sContact Nouv={"AMBOLAGE",
                        "Oscar",
                        "oscar.ambolage@latele.com",
                        {9,6,2002}};
  printf("***** Ajout d'un contact.\n");
  AjouterContact(&Nouv,Rep,&NbContacts);
  printf("***** Répertoire après ajout :\n");
  AfficherRepertoire(Rep,NbContacts);

  char Nom[]="DEUF"; // Nom qui va être recherché
  printf("\n***** Recherche de %s :\n",Nom);
  int Ind=Rechercher(Nom,Rep,NbContacts);
  if (Ind==-1)
    printf("%s n'est pas dans le repertoire.\n",Nom);
  else
    AfficherContact2(&(Rep[Ind]));

  char Fichier[]="repertoire.dat"; // Nom du fichier binaire
  printf("\n***** Écriture du répertoire dans le fichier %s.\n",Fichier);
  EcrireFichier(Rep,NbContacts,Fichier);

  struct sContact RepLu[LGMAXREP]; // Nouveau répertoire
  int NbContactsLus;

  printf("\n***** Lecture du répertoire depuis le fichier %s (v1).\n",Fichier);
  NbContactsLus=LireFichier1(RepLu,"repertoire.dat");
  printf("***** Répertoire lu :\n");
  AfficherRepertoire(RepLu,NbContactsLus);

  printf("\n***** Lecture du répertoire depuis le fichier %s (v2).\n",Fichier);
  NbContactsLus=LireFichier2(RepLu,"repertoire.dat");
  printf("***** Répertoire lu :\n");
  AfficherRepertoire(RepLu,NbContactsLus);

  printf("\n***** Tri du répertoire lu.\n");
  printf("***** Répertoire trié :\n");
  // ÉCRIRE ICI L'APPEL À LA FONCTION QSORT
  printf("---> Appel à qsort à écrire.\n"); // LIGNE À SUPPRIMER
  qsort(RepLu,NbContactsLus,sizeof(struct sContact),CompareContacts);
  AfficherRepertoire(RepLu,NbContactsLus);

  return 0;
}
