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
	#ifdef DEBOGAGE
	fprintf(stderr,"Fichier %s, ligne %d : Annee=%d, Mois=%d, Jour=%d, Heure=%d, Minute=%d\n"
					,__FILE__,__LINE__,date.annee,date.mois,date.jour,date.heure,date.minute);
	#endif
	if (date.annee>2050) return 0;
	if (date.mois>12||date.mois==0) return 0;
	if (date.jour>31||date.jour==0) return 0;
	if (date.heure>23) return 0;
	if (date.minute>59) return 0;
	if (date.mois==2){ // Gerer Fevrier
		if (date.jour==29){ //fevrier est de 29 jour max
			int bis = bissextile(date);
			if (bis==0 && date.jour==29) return 0;
			
		}
	
	}
	// Gestion des mois de 30 jour
	if ((date.mois==4 && date.jour==31) 
	||(date.mois==6 && date.jour==31)
	||(date.mois==9 && date.jour==31)
	||(date.mois==11 && date.jour==31) )
		return 0;	
	return 1; 
}

int Compare(const struct sDate reference, const struct sDate autreDate){
	if (reference.annee==autreDate.annee){
		if (reference.mois==autreDate.mois){
			if (reference.jour==autreDate.jour){
				if (reference.heure==autreDate.heure){
					if (reference.minute==autreDate.minute){
						return 0;
						#ifdef DEBOGAGE
						fprintf(stderr,"Fichier %s, ligne %d : Compare : Date egale\n"
									,__FILE__,__LINE__);
						#endif			
					}
					if (reference.minute<autreDate.minute)return -1;
					else return 1;				
				}
				if (reference.heure<autreDate.heure)return -1;
				else return 1;		
			}
			if (reference.jour<autreDate.jour)return -1;
			else return 1;
		}
		if (reference.mois<autreDate.mois)return -1;
		else return 1;	
	}
	if (reference.annee<autreDate.annee)return -1;
	#ifdef DEBOGAGE
	fprintf(stderr,"Fichier %s, ligne %d : Compare :  date 1 > date 2\n"
									,__FILE__,__LINE__);
	#endif
	return 1;
}

int Appartient(const struct sDate date, const struct sDate debut, const struct sDate fin){
	int temp; // Variable pour stocker les valeur de retour pour les tester
	temp = Compare(date,debut);
	if (temp==-1) return 0;
	temp = Compare(date,fin);
	if (temp==1) return 0;
	return 1;	
}

int Chevauche(const struct sDate debut1, const struct sDate fin1, const struct sDate debut2, const struct sDate fin2){
	int temp; // Variable pour stocker les valeur de retour pour les tester
	temp = Appartient(debut2,debut1,fin1);
	if (temp==1) return 1;
	temp = Appartient(debut1,debut2,fin2);
	if (temp==1) return 1;
	temp = Appartient(fin2,debut1,fin1);
	if (temp==1) return 1;
	temp = Appartient(fin1,debut2,fin2);
	if (temp==1) return 1;
	
	else return 0;
}

void YYYYMMDDTHHMM(char* destination, const struct sDate date){
	sprintf(destination,"%04d%02d%02dT%02d%02d",
			date.annee,
			date.mois,
			date.jour,
			date.heure,
			date.minute);
			
	#ifdef DEBOGAGE
	fprintf(stderr,"Fichier %s, ligne %d : Formatage de la date [ %s ] \n"
						,__FILE__,__LINE__,destination);
	#endif
}
