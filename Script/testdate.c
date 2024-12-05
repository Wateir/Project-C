#include "date.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>


void testEstValide() {
    // Test de dates valides
    
    struct sDate date1 = {2020, 2, 29, 0, 0};  
    assert(EstValide(date1) == 1);

    struct sDate date2 = {2023, 12, 31, 23, 59}; 
    assert(EstValide(date2) == 1);

    struct sDate date3 = {2024, 1, 1, 0, 0};   
    assert(EstValide(date3) == 1);

    struct sDate date4 = {2025, 8, 15, 12, 30};  
    assert(EstValide(date4) == 1);

    // Test de dates invalides
    struct sDate date5 = {2023, 4, 31, 0, 0};  
    assert(EstValide(date5) == 0);

    struct sDate date6 = {2023, 2, 29, 0, 0};  
    assert(EstValide(date6) == 0);

    struct sDate date7 = {2024, 1, 32, 0, 0};  
    assert(EstValide(date7) == 0);

    struct sDate date8 = {2024, 6, 0, 0, 0};   
    assert(EstValide(date8) == 0);

    struct sDate date9 = {2024, 13, 15, 0, 0}; 
    assert(EstValide(date9) == 0);

    struct sDate date10 = {2024, 5, -5, 0, 0}; 
    assert(EstValide(date10) == 0);

    struct sDate date11 = {2024, -1, 15, 0, 0}; 
    assert(EstValide(date11) == 0);

    struct sDate date12 = {2024, 5, 15, 25, 0};  
    assert(EstValide(date12) == 0);

    struct sDate date13 = {2024, 5, 15, 23, 60}; 
    assert(EstValide(date13) == 0);

    printf("Tous les tests ont réussi de EstValide\n");

}

void testCompare() {
    // Test 1 
    struct sDate date1 = {2023, 12, 25, 10, 30};
    struct sDate date2 = {2023, 12, 25, 10, 30};
    assert(Compare(date1, date2) == 0); 

    // Test 2 
    struct sDate date3 = {2023, 12, 25, 10, 30};
    struct sDate date4 = {2023, 12, 25, 11, 30};
    assert(Compare(date3, date4) < 0); 

    // Test 3 :
    struct sDate date5 = {2023, 12, 25, 12, 30};
    struct sDate date6 = {2023, 12, 25, 11, 30};
    assert(Compare(date5, date6) > 0); 

    // Test 4 
    struct sDate date7 = {2022, 12, 25, 10, 30};
    struct sDate date8 = {2023, 12, 25, 10, 30};
    assert(Compare(date7, date8) < 0); 

    // Test 5 
    struct sDate date9 = {2023, 11, 25, 10, 30};
    struct sDate date10 = {2023, 12, 25, 10, 30};
    assert(Compare(date9, date10) < 0); 

    // Test 6 
    struct sDate date11 = {2023, 12, 24, 10, 30};
    struct sDate date12 = {2023, 12, 25, 10, 30};
    assert(Compare(date11, date12) < 0); 

    // Test 7 
    struct sDate date13 = {2023, 12, 25, 9, 30};
    struct sDate date14 = {2023, 12, 25, 10, 30};
    assert(Compare(date13, date14) < 0); 

    // Test 8 
    struct sDate date15 = {2023, 12, 25, 10, 29};
    struct sDate date16 = {2023, 12, 25, 10, 30};
    assert(Compare(date15, date16) < 0);

    // Test 9 
    struct sDate date17 = {2023, 1, 1, 0, 0};
    struct sDate date18 = {2024, 1, 1, 0, 0};
    assert(Compare(date17, date18) < 0);

    printf("Tous les tests ont réussi de Compare\n");
}

void testAppartient() {
    // Test 1 : La date est exactement égale à la date de début
    struct sDate date1 = {2023, 5, 15, 10, 30};
    struct sDate debut1 = {2023, 5, 15, 0, 0};
    struct sDate fin1 = {2023, 5, 20, 23, 59};
    assert(Appartient(date1, debut1, fin1) == 1);

    // Test 2 : La date est exactement égale à la date de fin
    struct sDate date2 = {2023, 5, 20, 23, 59};
    struct sDate debut2 = {2023, 5, 15, 0, 0};
    struct sDate fin2 = {2023, 5, 20, 23, 59};
    assert(Appartient(date2, debut2, fin2) == 1);

    // Test 3 : La date est à l'intérieur de l'intervalle
    struct sDate date3 = {2023, 5, 17, 12, 0};
    struct sDate debut3 = {2023, 5, 15, 0, 0};
    struct sDate fin3 = {2023, 5, 20, 23, 59};
    assert(Appartient(date3, debut3, fin3) == 1);

    // Test 4 : La date est avant la date de début
    struct sDate date4 = {2023, 5, 14, 10, 30};
    struct sDate debut4 = {2023, 5, 15, 0, 0};
    struct sDate fin4 = {2023, 5, 20, 23, 59};
    assert(Appartient(date4, debut4, fin4) == 0);

    // Test 5 : La date est après la date de fin
    struct sDate date5 = {2023, 5, 21, 10, 30};
    struct sDate debut5 = {2023, 5, 15, 0, 0};
    struct sDate fin5 = {2023, 5, 20, 23, 59};
    assert(Appartient(date5, debut5, fin5) == 0);

    // Test 6 : Les dates de début et de fin sont égales
    struct sDate date6 = {2023, 5, 15, 0, 0};
    struct sDate debut6 = {2023, 5, 15, 0, 0};
    struct sDate fin6 = {2023, 5, 15, 0, 0};
    assert(Appartient(date6, debut6, fin6) == 1);

    // Test 7 : La date est avant le début et après la fin
    struct sDate date7 = {2023, 5, 14, 23, 59};
    struct sDate debut7 = {2023, 5, 15, 0, 0};
    struct sDate fin7 = {2023, 5, 20, 23, 59};
    assert(Appartient(date7, debut7, fin7) == 0);

    printf("Tous les tests ont réussi de Appartient \n");
}

void testChevauche() {
    // Test 1 : Les intervalles se chevauchent partiellement
    struct sDate debut1 = {2023, 5, 1, 0, 0};
    struct sDate fin1 = {2023, 5, 10, 23, 59};
    struct sDate debut2 = {2023, 5, 5, 0, 0};
    struct sDate fin2 = {2023, 5, 15, 23, 59};
    assert(Chevauche(debut1, fin1, debut2, fin2) == 1);

    // Test 2 : Les intervalles se chevauchent complètement
    struct sDate debut3 = {2023, 5, 1, 0, 0};
    struct sDate fin3 = {2023, 5, 10, 23, 59};
    struct sDate debut4 = {2023, 5, 3, 0, 0};
    struct sDate fin4 = {2023, 5, 8, 23, 59};
    assert(Chevauche(debut3, fin3, debut4, fin4) == 1);

    // Test 3 : Les intervalles sont séparés (avant l'un de l'autre)
    struct sDate debut5 = {2023, 5, 1, 0, 0};
    struct sDate fin5 = {2023, 5, 10, 23, 59};
    struct sDate debut6 = {2023, 5, 20, 0, 0};
    struct sDate fin6 = {2023, 5, 30, 23, 59};
    assert(Chevauche(debut5, fin5, debut6, fin6) == 0);

    // Test 4 : Un intervalle commence exactement à la fin de l'autre
    struct sDate debut7 = {2023, 5, 1, 0, 0};
    struct sDate fin7 = {2023, 5, 10, 23, 59};
    struct sDate debut8 = {2023, 5, 11, 0, 0};
    struct sDate fin8 = {2023, 5, 20, 23, 59};
    assert(Chevauche(debut7, fin7, debut8, fin8) == 0);

    // Test 5 : Les intervalles sont égaux
    struct sDate debut9 = {2023, 5, 1, 0, 0};
    struct sDate fin9 = {2023, 5, 10, 23, 59};
    struct sDate debut10 = {2023, 5, 1, 0, 0};
    struct sDate fin10 = {2023, 5, 10, 23, 59};
    assert(Chevauche(debut9, fin9, debut10, fin10) == 1); 

    // Test 6 : Le premier intervalle est avant le deuxième
    struct sDate debut11 = {2023, 4, 1, 0, 0};
    struct sDate fin11 = {2023, 4, 10, 23, 59};
    struct sDate debut12 = {2023, 5, 1, 0, 0};
    struct sDate fin12 = {2023, 5, 10, 23, 59};
    assert(Chevauche(debut11, fin11, debut12, fin12) == 0);

    // Test 7 : Le premier intervalle commence à la même date que la fin du deuxième
    struct sDate debut13 = {2023, 5, 1, 0, 0};
    struct sDate fin13 = {2023, 5, 10, 23, 59};
    struct sDate debut14 = {2023, 5, 10, 0, 0};
    struct sDate fin14 = {2023, 5, 20, 23, 59};
    assert(Chevauche(debut13, fin13, debut14, fin14) == 1);

    printf("Tous les tests ont réussi de Chevauche\n");
}

void testYYYYMMDDTHHMM() {
    char destination[15]; 

    // Test 1 
    struct sDate date1 = {2023, 11, 29, 15, 45};
    YYYYMMDDTHHMM(destination, date1);
    assert(strcmp(destination, "20231129T1545") == 0);

    // Test 2 
    struct sDate date2 = {1999, 5, 1, 8, 30};
    YYYYMMDDTHHMM(destination, date2);
    assert(strcmp(destination, "19990501T0830") == 0);

    // Test 3 
    struct sDate date3 = {2024, 2, 29, 12, 0};  
    YYYYMMDDTHHMM(destination, date3);
    assert(strcmp(destination, "20240229T1200") == 0);

    // Test 4     
    struct sDate date4 = {2020, 12, 31, 23, 59};
    YYYYMMDDTHHMM(destination, date4);
    assert(strcmp(destination, "20201231T2359") == 0);

    // Test 5 
    struct sDate date5 = {2025, 1, 1, 0, 0};
    YYYYMMDDTHHMM(destination, date5);
    assert(strcmp(destination, "20250101T0000") == 0);

    printf("Tous les tests ont réussi de YYYYMMDDTHHMM\n");
}

int main(void) {
    // Appel de la fonction de test
    testEstValide();
    testCompare();
    testAppartient();
    testChevauche();
    testYYYYMMDDTHHMM();
    return 0;
}

