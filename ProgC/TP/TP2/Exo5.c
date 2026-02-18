#include <stdio.h>
#define NBR_TAB 21 // Mettre un de plus que le chiffre voulu

int main(void){
    printf("  x |");fflush(stdout);
    for (int i=0;i<NBR_TAB;i++){
        printf("%4d",i);
    }
    printf("\n");
    printf("------");
    for (int i=0;i<NBR_TAB;i++){
        printf("----");
    }
    printf("\n");

    for (int i=0;i<NBR_TAB;i++){
        printf("%3d |",i);
        for(int j=0;j<NBR_TAB;j++){
            printf("%4d",i*j);
        }
        printf("\n");
    }
}
