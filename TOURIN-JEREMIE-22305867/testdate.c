#include "date.h"
#include <stdio.h>
#include <assert.h>

void testEstValide() {
    // Test de dates valides
    struct sDate date1 = {2020, 2, 29, 0, 0};  // Année bissextile
    assert(EstValide(date1) == 1);

    struct sDate date2 = {2023, 12, 31, 23, 59}; // Dernier jour de l'année, à 23h59
    assert(EstValide(date2) == 1);

    struct sDate date3 = {2024, 1, 1, 0, 0};   // Premier jour de l'année
    assert(EstValide(date3) == 1);

    struct sDate date4 = {2025, 8, 15, 12, 30};  // Date valide au milieu de l'année
    assert(EstValide(date4) == 1);

    // Test de dates invalides
    struct sDate date5 = {2023, 4, 31, 0, 0};  // Avril a 30 jours, donc 31 est invalide
    assert(EstValide(date5) == 0);

    struct sDate date6 = {2023, 2, 29, 0, 0};  // 2023 n'est pas une année bissextile
    assert(EstValide(date6) == 0);

    struct sDate date7 = {2024, 1, 32, 0, 0};  // Janvier a seulement 31 jours
    assert(EstValide(date7) == 0);

    struct sDate date8 = {2024, 6, 0, 0, 0};   // Le jour ne peut pas être 0
    assert(EstValide(date8) == 0);

    struct sDate date9 = {2024, 13, 15, 0, 0}; // Le mois 13 n'existe pas
    assert(EstValide(date9) == 0);

    struct sDate date10 = {2024, 5, -5, 0, 0}; // Jour négatif (invalide)
    assert(EstValide(date10) == 0);

    struct sDate date11 = {2024, -1, 15, 0, 0}; // Mois négatif (invalide)
    assert(EstValide(date11) == 0);

    struct sDate date12 = {2024, 5, 15, 25, 0}; // Heure invalide (25 est hors de portée)
    assert(EstValide(date12) == 0);

    struct sDate date13 = {2024, 5, 15, 23, 60}; // Minute invalide (60 est hors de portée)
    assert(EstValide(date13) == 0);

    printf("Tous les tests ont réussi !\n");

}

int main(void) {
    // Appel de la fonction de test
    testEstValide();
    return 0;
}

