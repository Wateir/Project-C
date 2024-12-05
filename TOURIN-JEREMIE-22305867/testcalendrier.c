#include "calendrier.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


void testAjouterEvenement() {
	// Test 1
	tCalendrier* cal;
    struct sDate debut1 = {2024, 12, 25, 10, 30};
    struct sDate fin1 = {2024, 12, 25, 12, 0};
    tEvenement ev1 = CreerEvenement("Valide", debut1, fin1);

    AjouterEvenement(cal,ev1);

    tEvenement result1 = PremierEvenement(*cal);
    struct sDate debRes = Debut(result1);
    struct sDate finRes = Fin(result1);

    assert(Compare(debRes,debut1)==0 && Compare(finRes,fin1)==0);


    printf("Tous les tests ont réussi de CreeEvenement\n");
}
int main(void){
	return 0;
}
