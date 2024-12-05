#include "calendrier.h"
#include "date.h"
#include "evenement.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAILLE_CALENDRIER_MAX 100

struct sCalendrier {
	tEvenement pEvenement ;
	tCalendrier pSuivant ;
};

typedef struct sCalendrier* tCalendrier;

// Retourne le pointeur vers un sCalendrier vide, avec pSuivant à "NULL"
// Retourne NULL en cas de probleme
// Retourne le calendrier sinon
static tCalendrier CreerCalendrier(){
	tCalendrier temp = malloc(sizeof(struct sCalendrier));
	#ifdef DEBOGAGE
	fprintf(stderr, "Fichier %s, ligne %d : Création Calendrier\n", __FILE__, __LINE__);
	#endif
	if (temp == NULL) {
		return NULL;
	}
	temp->pSuivant = NULL;
	return temp;
}

// Retourne 0 si l'evenement nouveau est sur une periode differente, et que le titre est different
// Retourne -1 sinon
static int EstPossible (tEvenement nouveau, tEvenement ancien){
	char* titre1 = Titre(nouveau);
	char* titre2 = Titre(ancien);
	if (strcmp(titre1, titre2) == 0){
		#ifdef DEBOGAGE
		fprintf(stderr, "Fichier %s, ligne %d : Titre Invalide, deja donné\n", __FILE__, __LINE__);
		#endif	
		return -1;
	}
	struct sDate debut1 = Debut(nouveau);
	struct sDate debut2 = Debut(ancien);
	struct sDate fin1 = Fin(nouveau);
	struct sDate fin2 = Fin(ancien);
	if (Chevauche(debut1,debut2,fin1,fin2) == 0){
		#ifdef DEBOGAGE
		fprintf(stderr, "Fichier %s, ligne %d : Chevauchement des Dates\n", __FILE__, __LINE__);
		#endif	
		return -1;		
	}
	return 0;
}

static void LibererCalendrier(tCalendrier addr[],int NbTab){
	for (int j=0;j<NbTab;j++){
		free(addr[j]);
	}
}

int AjouterEvenement(tCalendrier* pCalendrier, tEvenement evenement) {
    tCalendrier current = *pCalendrier;

    
	if (pCalendrier != NULL){
		tCalendrier i;
		// Test de si l'evenement donné est compatible avec ceux deja existant
		i = (*pCalendrier)->pSuivant;
		while (i!=NULL){
			if (EstPossible(i->pEvenement,evenement)==-1) return -1;
			i = i->pSuivant;
		}
    	while (current->pSuivant != NULL) {
        	current = current->pSuivant;
    	}
    	current = CreerCalendrier();    	
    }

    // Le calendrier n'existe pas, initialisation
    else {
    	current = CreerCalendrier();
    }
    if (current==NULL){
    	#ifdef DEBOGAGE
    	fprintf(stderr, "Fichier %s, ligne %d : Erreur d'allocation mémoire [AjouterEvenement]\n", __FILE__, __LINE__);
    	#endif
    	return -1;
    }
    current->pEvenement = evenement;
    return 0;

}

tEvenement PremierEvenement(tCalendrier calendrier){
	return calendrier->pEvenement;
}

tCalendrier SuiteDuCalendrier(tCalendrier calendrier){
	return calendrier->pSuivant;
}

void DetruitCalendrier(tCalendrier* pCalendrier){
    if (pCalendrier == NULL || *pCalendrier == NULL) {
    	#ifdef DEBOGAGE
    	fprintf(stderr, "Fichier %s, ligne %d : Calendrier donné est vide [DetruitCalendrier]\n", __FILE__, __LINE__);
    	#endif
        return; // Pas de calendrier à libérer
    }
    tCalendrier temp = *pCalendrier;
    tCalendrier addr[TAILLE_CALENDRIER_MAX];
    int i = 0;
	while (temp!=NULL){
		addr[i]=temp;
		i++;
	}
	LibererCalendrier(addr,i);
	*pCalendrier=NULL;
	
}

void AfficheCalendrier(tCalendrier calendrier){
	tCalendrier temp = calendrier;
	while(temp!= NULL){
		AfficheEvenement(temp->pEvenement);
		temp = temp->pSuivant;
	}
}

int SupprimeEvenementsPeriode(tCalendrier* pCalendrier, struct sDate debut, struct sDate fin){
	tCalendrier temp = *pCalendrier,addr[TAILLE_CALENDRIER_MAX];
	int i=0,flag=0,NbCal=0;  //Flag pour gerer l'update du pointeur
	
	while(temp!= NULL){
		struct sDate debut2 = Debut(temp->pEvenement);
		struct sDate fin2 = Fin(temp->pEvenement);
		if (Chevauche(debut,fin,debut2,fin2)==1){
			addr[i] = temp;
			i++;
			if (flag==1) pCalendrier = &temp;
			if (temp==*pCalendrier) flag = 1;
			
		}
		NbCal++;
		temp = temp->pSuivant;
	}
	if (i==NbCal)*pCalendrier=NULL; // Le calendrier est vide
	
	LibererCalendrier(addr,i);
	return i;
}

int ExportCalendrier(tCalendrier calendrier, const char* fichier){
	FILE *fich=fopen(fichier, "wb");
	  if (fich == NULL) {
	  		  #ifdef DEBOGAGE
	  		  fprintf(stderr, "Fichier %s, ligne %d : Erreur d'ouverture du fichier [ExportCalendrier]\n", __FILE__, __LINE__);
	  		  #endif
	          return -1;  
	   }
	  int i=0,max;
	  tCalendrier pCon= calendrier;
	  if (pCon == NULL) {
	      fprintf(stderr, "Erreur : le calendrier est vide\n");
	      #ifdef DEBOGAGE
	      fprintf(stderr, "Fichier %s, ligne %d : Erreur : le calendrier est vide [ExportCalendrier]\n", __FILE__, __LINE__);
	      #endif
	      fclose(fich);
	      return -1;
	  }
	  max=fwrite((pCon->pEvenement),sizeof(tEvenement),100,fich);
	  while (max>i){
	    fwrite((pCon->pEvenement),sizeof(tEvenement),max,fich);
	    pCon=pCon->pSuivant;
	    i++;
	  }
	  fclose(fich);
	  return 0;
}
