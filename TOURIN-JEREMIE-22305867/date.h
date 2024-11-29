#ifndef __DATE_H__
#define __DATE_H__

#define DEBOGAGE // Supprimer le no pour avoir un programme plus verbeux

#define TAILLE_CHAINE_DATE 13 + 1

struct sDate {
    unsigned int annee;
    unsigned char mois;
    unsigned char jour;
    unsigned char heure;
    unsigned char minute;
};

/*
 * Vérifie si une date est valide, en tenant compte de la durée en jours
 * des différents mois ainsi que des éventuelles années bissextiles
 * Retourne 1 si la date est valide, 0 sinon
 */
extern int EstValide(const struct sDate);

/*
 * Compare deux dates par ordre chronologique
 * Entrées : la date de réference suivie de celle à comparer
 * Retourne 0 si les deux dates sont égales, une valeur négative si la première est antérieure à la seconde, une valeur positive sinon
 */
extern int Compare(const struct sDate reference, const struct sDate autreDate);

/*
 * Vérifie si une date est comprise entre une date de début et une date de fin
 * Entrées : la date à tester, les dates de début et de fin de l'intervalle
 * Retourne 1 si la date est comprise entre les deux autres, 0 sinon
 */
extern int Appartient(const struct sDate date, const struct sDate debut, const struct sDate fin);

/*
 * Vérifie si deux intervalles de dates se chevauchent
 * Entrées : les dates de début et de fin des deux intervalles
 * Retourne 1 si les intervalles se chevauchent, 0 sinon
 */
extern int Chevauche(const struct sDate debut1, const struct sDate fin1, const struct sDate debut2, const struct sDate fin2);

/*
 * Délivre en sortie la représentation d'une date sous forme d'une chaîne de 13+1 caractères au format YYYYMMDDTHHMM
 * Entrée : date à convertir
 * Sortie : adresse de la chaîne de caractères préalablement allouée, susceptible de recevoir 13+1 caractères
 * Remarque : l'allocation et la désallocation de la chaîne de caractères sont à la charge de l'appelant
 */
extern void YYYYMMDDTHHMM(char* destination, const struct sDate date);

#endif
