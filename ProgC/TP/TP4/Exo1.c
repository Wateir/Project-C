#include <stdio.h>

void AfficherTab(int Tab[],int NbElt){
    printf("[%d",Tab[0]);
    for (int i=1;i<NbElt;i++){
        printf(", %d",Tab[i]);
    }
    printf("]\n");
}

int min(int Tab[],int NbElt){
    int min=Tab[0];

    for (int i =1;i<NbElt;i++){
        if (min>Tab[i]) min =Tab[i];
    }
    return min;
}

int max(int Tab[],int NbElt){
    int max=Tab[0];

    for (int i =1;i<NbElt;i++){
        if (max<Tab[i]) max =Tab[i];
    }
    return max;
}

void MinMax(int Tab[], int NbElt, int **pMin, int **pMax){
    int iMax=Tab[0], iMin=Tab[0];
    *pMax=&Tab[0]; *pMin=&Tab[0];

    for (int i=1;i<NbElt;i++){
        if (iMax<Tab[i])*pMax=&Tab[i];
        if (iMin>Tab[i])*pMax=&Tab[i];
    }
}

int SupprimerVal(int Tab[], int *pNbElt, int Val) {
    int NbSupr = 0;

    for (int lecture = 0, ecriture = 0; lecture < *pNbElt; lecture++) {
        if (Tab[lecture] != Val) {
            Tab[ecriture] = Tab[lecture];
            ecriture++;
        } else {
            NbSupr++;
        }

        #ifdef DEBUG
            printf("debug : ");
            printf("Tab[lecture] : %d, ", Tab[lecture]);
            printf("Tab[ecriture] : %d ", Tab[ecriture]);
            AfficherTab(Tab, *pNbElt);
        #endif
    }

    *pNbElt -= NbSupr;
    return NbSupr;
}


int main(void){
    int tab[]={1,2,3,4};
    int *min,*max;
    AfficherTab(tab,4);
    MinMax(tab,4,&min,&max);
    printf("Min: %d\n", *min);
    printf("Max: %d\n", *max);


    int NbElt = 6;
    int tab2[]={1,2,3,4,3,5};
    AfficherTab(tab2,NbElt);
    SupprimerVal(tab2,&NbElt, 3);
    AfficherTab(tab2,NbElt);
    return 0;
}
