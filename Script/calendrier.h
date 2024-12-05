#ifndef __CALENDRIER_H__
#define __CALENDRIER_H__

#include "evenement.h"

typedef struct sCalendrier* tCalendrier;

/*
 * Ajoute un événement à un calendrier s'il n'existe pas déjà un événement portant le même titre
 * et si les dates de début et de fin ne se chevauchent pas avec un autre événement du calendrier
 * Entrée : un événement
 * Mise à jour : pointeur vers le calendrier
 * Retourne 0 si l'ajout a été effectué, -1 sinon
 * Remarque : dans le cas de l'ajout à un Calendrier vide, le pointeur qui représente le calendrier est modifié
 */
extern int AjouterEvenement(tCalendrier* pCalendrier, tEvenement evenement);

/*
 * Entrée : un calendrier supposé non vide
 * Retourne le premier événement d’un calendrier
 */
extern tEvenement PremierEvenement(tCalendrier calendrier);

/*
 * Entrée : un calendrier supposé non vide
 * Retourne l'adresse de la deuxième cellule de la liste chaînée qui constitue un calendrier
 */
extern tCalendrier SuiteDuCalendrier(tCalendrier calendrier);

/*
 * Libère les ressources affectées à un calendrier et force le pointeur correspondant à NULL
 * Mise à jour : un pointeur vers un calendrier
 */
extern void DetruitCalendrier(tCalendrier* pCalendrier);

/*
 * Affiche le calendrier sur la sortie standard
 * Entrée : un calendrier
 */
extern void AfficheCalendrier(tCalendrier calendrier);

/*
 * Supprime et libère tous les événements d’un calendrier qui chevauchent (au sens du module date)
 *  une période définie par un date de début et une date de fin
 * Entrées : la date de début et la date de fin de la période à supprimer
 * Mise à jour : pointeur vers le calendrier
 * Retourne le nombre d'événements supprimés
 * Dans le cas où tous les événements ont été supprimés, le calendrier est mis à jour
 * pour correspondre à un calendrier vide.
 */
extern int SupprimeEvenementsPeriode(tCalendrier* pCalendrier, struct sDate debut, struct sDate fin);

/*
 * Écriture d'un calendrier au format ical dont le nom est passé en paramètre
 * Entrées : le calendrier à écrire et le nom du fichier à créer
 * Retourne 0 si l'export a réussi, -1 sinon (quelle que soit la raison)
 */
extern int ExportCalendrier(tCalendrier calendrier, const char* fichier);

#endif
