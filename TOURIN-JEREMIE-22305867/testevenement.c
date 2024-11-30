#include "evenement.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testCreerEvenement() {
    struct sDate debut1 = {2024, 12, 25, 10, 30};
    struct sDate fin1 = {2024, 12, 25, 12, 0};
    tEvenement ev1 = CreerEvenement("Valide", debut1, fin1);
    assert(ev1 != NULL);
    
    struct sDate debut2 = {2024, 12, 25, 12, 0};
    struct sDate fin2 = {2024, 12, 25, 10, 30};
    tEvenement ev2 = CreerEvenement("NULL", debut2, fin2);
    
    assert(ev2 == NULL);

    struct sDate debut3 = {2024, 13, 25, 10, 30};
    struct sDate fin3 = {2024, 12, 25, 12, 0};
    tEvenement ev3 = CreerEvenement("13", debut3, fin3);
    assert(ev3 == NULL);
    
    struct sDate debut4 = {2024, 12, 25, 10, 30};
    struct sDate fin4 = {2024, 2, 30, 12, 0};
    tEvenement ev4 = CreerEvenement("debut>fin", debut4, fin4);
    assert(ev4 == NULL);

    struct sDate debut5 = {2024, 12, 31, 9, 0};
    struct sDate fin5 = {2024, 12, 31, 10, 0};  
    tEvenement ev5 = CreerEvenement("A", debut5, fin5);
    assert(ev5 != NULL);

    printf("Tous les tests ont réussi de CreeEvenement\n");
}

void testTitre() {
    struct sDate debut1 = {2024, 12, 25, 10, 30};
    struct sDate fin1 = {2024, 12, 25, 12, 0};
    tEvenement ev1 = CreerEvenement("Event incroyable", debut1, fin1);
    char* titre1 = Titre(ev1);
    assert(strcmp(titre1, "Event incroyable") == 0);

    struct sDate debut2 = {2024, 12, 31, 9, 0};
    struct sDate fin2 = {2024, 12, 31, 10, 0};
    tEvenement ev2 = CreerEvenement("A", debut2, fin2);
    char* titre2 = Titre(ev2);
    assert(strcmp(titre2, "A") == 0);
    
    struct sDate debut3 = {2024, 12, 31, 9, 0};
    struct sDate fin3 = {2024, 12, 31, 10, 0};
    tEvenement ev3 = CreerEvenement("", debut3, fin3);
    char* titre3 = Titre(ev3);
    assert(strcmp(titre3, "") == 0); 


    printf("Tous les tests ont réussi de Titre\n");
}

void testAfficherEvenement(){
	struct sDate debut3 = {2024, 12, 31, 9, 0};
	struct sDate fin3 = {2024, 12, 31, 10, 0};
	tEvenement ev3 = CreerEvenement("AfficherEvent", debut3, fin3);
	AfficheEvenement(ev3);

	printf("Tous les tests ont réussi de AfficheEvenement\n");
	
}


int main() {
    testCreerEvenement();
    testTitre();
    testAfficherEvenement();
    return 0;
}
