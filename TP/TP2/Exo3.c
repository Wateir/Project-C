#include <stdio.h>
#define MAX_LENGHT 512

int main(void){
    int nbval;
    int val[MAX_LENGHT];
    printf("Nombre de valeur que vous voulez rentrer : ");fflush(stdout);
    scanf("%d",&nbval);

    printf("Entrer les valeurs :\n");
    for(int i=0;i<nbval;i++){
        scanf("%d",&val[i]);
    }

    float somme;
    for(int i=0;i<nbval;i++){
        somme = val[i];
    }

    printf("Moy = %.1f\n",somme/nbval);
    return 0;
}
