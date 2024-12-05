#include "calendrier.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


void test_ajouter_evenement() {
    // Initialisation d'un calendrier vide
    tCalendrier calendrier = { .nbEvenements = 0 };
    
    // Cas 1: Ajouter un événement à un calendrier vide
    tEvenement evenement1 = {"Meeting", "2024-12-05 09:00", "2024-12-05 10:00"};
    int result = AjouterEvenement(&calendrier, evenement1);
    assert(result == 0);
    assert(calendrier.nbEvenements == 1); // Vérifie que l'événement a été ajouté
    
    // Cas 2: Ajouter un événement avec un titre déjà existant
    tEvenement evenement2 = {"Meeting", "2024-12-05 11:00", "2024-12-05 12:00"};
    result = AjouterEvenement(&calendrier, evenement2);
    assert(result == -1); // L'ajout doit échouer à cause du titre dupliqué
    assert(calendrier.nbEvenements == 1); // Le nombre d'événements ne change pas
    
    
    // Si tous les tests passent
    printf("Tous les tests ont réussi de AjouterEvenement\n");
}

int main(void){
	test_ajouter_evenement();
	return 0;
}
