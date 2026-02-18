#include <stdio.h>

#define INPUT "fich.txt"
#define TAILLE_MOT 26
#define TAILLE_GABARIT 4

int main(void){
    int NombreMot=0;
    FILE* fichier = fopen(INPUT,"rt");
    if (fichier == NULL){
        perror(INPUT);
        return 1;
    }
    char tampon[TAILLE_MOT+1];
    char gabarit[TAILLE_GABARIT+1];
    sprintf(gabarit, "%%%ds",TAILLE_MOT);
    int val = fscanf(fichier,"%s",tampon);
    while (val != 0){
        NombreMot ++;
        int val = fscanf(fichier,"%s",tampon);
    }

    fclose(fichier);
    printf("%d",NombreMot);
    return 0;
}
