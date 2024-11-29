#ifndef __EVENEMENT_H__
#define __EVENEMENT_H__

#include "date.h"

typedef struct sEvenement* tEvenement;

/*
 * Crée un événement à partir de son titre et de ses dates de début et de fin.
 * Entrées : le titre de l'événement, la date de début et la date de fin
 * Retourne l'événement créé, ou NULL si les dates ne sont pas valides ou si la date de fin est antérieure à la date de début
 * Remarque : le titre passé en paramètre est recopié dans une nouvelle zone allouée dynamiquement par cette fonction
 */
extern tEvenement CreerEvenement(const char* titre, struct sDate debut, struct sDate fin);

/*
 * Entrée : l'événement
 * Retourne l'adresse du premier caractère du titre de l'événement
 */
extern char* Titre(tEvenement evenement);

/*
 * Entrée : l'événement
 * Retourne la date de début de l'événement
 */
extern struct sDate Debut(tEvenement evenement);

/*
 * Entrée : l'événement
 * Retourne la date de fin de l'événement
 */
extern struct sDate Fin(tEvenement evenement);

/*
 * Libère la mémoire allouée pour un événement (y compris son titre) et le force à NULL
 */
extern void DetruitEvenement(tEvenement* pEvenement);

/*
 * Affiche un évenement sur la sortie standard
 */
extern void AfficheEvenement(tEvenement evenement);

#endif
