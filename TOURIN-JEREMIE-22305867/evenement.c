#include "evenement.h"
#include "date.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct sEvenement {
    char* titre;
	struct sDate Debut;
	struct sDate Fin;
};

typedef struct sEvenement* tEvenement;

static char* AllouerTitre(const char* titre){
	int longueur = strlen(titre);

	char* dublicata = malloc((longueur +1) * sizeof(char));
	if (dublicata == NULL) {
		#ifdef DEBOGAGE
		fprintf(stderr,"Fichier %s, ligne %d : Erreur d'allocation mémoire [Allouer Titre]\n",__FILE__,__LINE__);
		#endif
		return NULL;
	}
	strcpy(dublicata, titre);
	return dublicata;
}

tEvenement CreerEvenement(const char* titre, struct sDate debut, struct sDate fin){
	tEvenement event = malloc(sizeof(struct sEvenement));
	if (event==NULL) {
		#ifdef DEBOGAGE
		fprintf(stderr,"Fichier %s, ligne %d : Erreur d'allocation mémoire [Allouer Evenement]\n",__FILE__,__LINE__);
		#endif
	}
	event->titre = AllouerTitre(titre);
	if (event->titre==NULL) return NULL;

	int temp = EstValide(debut);
	if (temp==0){
		#ifdef DEBOGAGE
		fprintf(stderr,"Fichier %s, ligne %d : struct sDate [ debut ] invalide\n",__FILE__,__LINE__);
		#endif
		return NULL;
	}
	temp = EstValide(fin);
	if (temp==0){
		#ifdef DEBOGAGE
		fprintf(stderr,"Fichier %s, ligne %d : struct sDate [ fin ] invalide\n",__FILE__,__LINE__);
		#endif
		return NULL;
	}
	temp = Compare(debut,fin);
	if (temp!=-1){
		#ifdef DEBOGAGE
		fprintf(stderr,"Fichier %s, ligne %d : Temporalité de sEvenement invalide\n [debut]=[fin] ou [debut]>[fin]\n",__FILE__,__LINE__);
		#endif
		return NULL;
	}

	event->Debut.annee = debut.annee;
	event->Debut.mois = debut.mois; 
	event->Debut.jour = debut.jour; 
	event->Debut.heure = debut.heure; 
	event->Debut.minute = debut.minute; 

	event->Fin.annee = fin.annee;
	event->Fin.mois = fin.mois; 
	event->Fin.jour = fin.jour; 
	event->Fin.heure = fin.heure; 
	event->Fin.minute = fin.minute; 

	return event;	
}

char* Titre(tEvenement evenement){
	char * addr;
	addr = evenement->titre;
	return addr;
}

struct sDate Debut(tEvenement evenement){
	struct sDate retourner;
	retourner.annee = evenement->Debut.annee;
	retourner.mois = evenement->Debut.mois;
	retourner.jour = evenement->Debut.jour;
	retourner.heure = evenement->Debut.heure;
	retourner.minute = evenement->Debut.minute;

	return retourner;
}

struct sDate Fin(tEvenement evenement){
	struct sDate retourner;
	retourner.annee = evenement->Fin.annee;
	retourner.mois = evenement->Fin.mois;
	retourner.jour = evenement->Fin.jour;
	retourner.heure = evenement->Fin.heure;
	retourner.minute = evenement->Fin.minute;

	return retourner;	
}
