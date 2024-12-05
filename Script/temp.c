#include "calendrier.h"
#include "date.h"
#include "evenement.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
