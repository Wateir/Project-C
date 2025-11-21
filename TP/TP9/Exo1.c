#include "image.h"
#include "ti.h"
#include <stdlib.h>

int main(void){
    char *fichier = "paysage.pgm";
    tImage Im = ImLire(fichier);
    if (Im == NULL){
        #ifdef DEBUG
            printf("ImLire a loupé\n");
        #endif
        return 1;
    }
    unsigned char* table = malloc(sizeof(unsigned char)*GRIS_MAX);
    RemplirTableInversion(table);
    tImage ImNegatif = AppliquerTable(table,Im);
    ImEcrire(ImNegatif,"paysageNegatif.pgm");
    RemplirTableGamma(0.4, table);
    ImNegatif = AppliquerTable(table,Im);
    ImEcrire(ImNegatif,"paysageGamma04.pgm");
    RemplirTableGamma(2.5, table);
    ImNegatif = AppliquerTable(table,Im);
    ImEcrire(ImNegatif,"paysageGamma25.pgm");

    int NbLig = ImNbLig(Im);
    ImLiberer(&Im,NbLig);
    ImLiberer(&ImNegatif,NbLig);

    return 0;
}
