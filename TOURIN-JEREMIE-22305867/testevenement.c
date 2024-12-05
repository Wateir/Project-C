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

void testDebut() {
    // Test 1 
    struct sDate debut1 = {2024, 12, 25, 10, 30};
    struct sDate fin1 = {2024, 12, 25, 12, 0};
    tEvenement ev1 = CreerEvenement("Event incroyable", debut1, fin1);
    
    struct sDate result1 = Debut(ev1);
    
    assert(Compare(result1,debut1)==0);
    
    // Test 2 
    struct sDate debut2 = {2025, 1, 1, 9, 0};
    struct sDate fin2 = {2025, 1, 1, 11, 0};
    tEvenement ev2 = CreerEvenement("Nouvel An", debut2, fin2);

    struct sDate result2 = Debut(ev2);
    
    assert(Compare(result2,debut2)==0);    
    
    // Test 3
    struct sDate debut3 = {2023, 7, 4, 18, 45};
    struct sDate fin3 = {2023, 7, 4, 20, 0};
    tEvenement ev3 = CreerEvenement("BBQ Party", debut3, fin3);
    
    struct sDate result3 = Debut(ev3);
    
    assert(Compare(result3,debut3)==0);  
    printf("Tous les tests ont réussi pour la Debut\n");
}

void testFin() {
    // Test 1 
    struct sDate debut1 = {2024, 12, 25, 10, 30};
    struct sDate fin1 = {2024, 12, 25, 12, 0};
    tEvenement ev1 = CreerEvenement("Event incroyable", debut1, fin1);
    
    struct sDate result1 = Fin(ev1);
    
    assert(Compare(result1,fin1)==0);
    
    // Test 2 
    struct sDate debut2 = {2025, 1, 1, 9, 0};
    struct sDate fin2 = {2025, 1, 1, 11, 0};
    tEvenement ev2 = CreerEvenement("Nouvel An", debut2, fin2);

    struct sDate result2 = Fin(ev2);
    
    assert(Compare(result2,fin2)==0);    
    
    // Test 3
    struct sDate debut3 = {2023, 7, 4, 18, 45};
    struct sDate fin3 = {2023, 7, 4, 20, 0};
    tEvenement ev3 = CreerEvenement("BBQ Party", debut3, fin3);
    
    struct sDate result3 = Fin(ev3);
    
    assert(Compare(result3,fin3)==0);  
    printf("Tous les tests ont réussi pour la fonction Debut !\n");
}

void testAfficherEvenement(){
	struct sDate debut3 = {2024, 12, 31, 9, 0};
	struct sDate fin3 = {2024, 12, 31, 10, 0};
	tEvenement ev3 = CreerEvenement("AfficherEvent", debut3, fin3);
	AfficheEvenement(ev3);

	printf("Tous les tests ont réussi de Fin\n");
	
}


int main() {
    testCreerEvenement();
    testTitre();
    testDebut();
    testFin();
    testAfficherEvenement();
    return 0;
}
