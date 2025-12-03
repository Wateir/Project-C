#include <stdio.h>
#define FICHIER_SOURCE "fichier-source.dat"
#define FICHIER_DESTINATION "fichier-destination.dat"

#define CHUNKS 512

int main(void){
    FILE* input = fopen(FICHIER_SOURCE,"rb");
    if (input == NULL){
        perror(FICHIER_SOURCE);
        return 1;
    }
    FILE* output = fopen(FICHIER_DESTINATION,"wb");
    if (output == NULL){
        perror(FICHIER_SOURCE);
        return 1;
    }
    return 0;
}
