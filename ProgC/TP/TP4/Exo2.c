#include <stdio.h>

int decomposeSec(int secIn,int *heure,int *minute,int *seconde){
    *heure = secIn/3600;
    *minute= (secIn%3600)/60;
    *seconde= ((secIn%3600)%60);

    return 0;
}

int secondeDansTableau(int seconde,int tab[3]){
    decomposeSec(seconde,&tab[0],&tab[1],&tab[2]);
    return 0;
}

int main(void){
    int input,tab[3];
    scanf("%d",&input);

    secondeDansTableau(input,tab);
    printf("%dh%dmin%dsec\n",tab[0],tab[1],tab[2]);

    return 0;
}
