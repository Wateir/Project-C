#include <stdio.h>

#define INPUT "fich.txt"

int main(void){
    int NombreMot=0;
    FILE* fichier = fopen(INPUT,"rt");
    if (fichier == NULL){
        perror(INPUT);
        return 1;
    }
    char tampon[26+1];
    int val = fscanf(fichier,"%s",tampon);
    while (val != 0){
        NombreMot ++;
        int val = fscanf(fichier,"%s",tampon);
    }

    fclose(fichier);
    printf("%d",NombreMot);
    return 0;
}
