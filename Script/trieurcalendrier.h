#ifndef __TRIEURCALENDRIER_H__
#define __TRIEURCALENDRIER_H__

#include "calendrier.h"

/*
 * Tri par ordre croissant des dates de début les événements d'un calendrier
 * Entrée : un calendrier non vide. La structure interne du calendrier est modifiée pour correspondre à une liste triée d'évenements
 */
extern void TriCalendrier(tCalendrier calendrier);

#endif
