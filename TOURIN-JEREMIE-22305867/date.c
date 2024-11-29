#include "date.h"
#include <stdio.h>

/*
 * Verifie si l'année bissextiles
 * Retourne 1 si la date est valide, 0 sinon
 */
static int bissextile(const struct sDate date) {
	#ifdef DEBOGAGE
	fprintf(stderr,"Fichier %s, ligne %d : Appel de Bissextile\n",__FILE__,__LINE__);
	#endif
	if (date.annee % 4==0){
		if (date.annee % 100==0){
			if (date.annee % 400==0) return 1;
			return 1;
		}
		return 1;
	}
	return 0;
}

int EstValide(const struct sDate date){
	if (date.annee>2050) return 0;
	if (date.mois>12) return 0;
	if (date.jour>31) return 0;
	if (date.heure>12) return 0;
	if (date.minute>60) return 0;
	if (date.mois==2){ // Gerer Fevrier
		if (date.jour>29){ //fevrier est de 29 jour max
			int bis = bissextile(date);
			if (bis==0 && date.jour==29) return 0;
			
		}
	#ifdef DEBOGAGE
	fprintf(stderr,"Fichier %s, ligne %d : Annee=%d, Mois=%d, Jour=%d, Heure=%d, Minute=%d\n"
				,__FILE__,__LINE__,date.annee,date.mois,date.jour,date.heure,date.minute);
	#endif
	}
	
	return 1; 
}
