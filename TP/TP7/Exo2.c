#include <stdio.h>
#include <stdlib.h>
#define LENGTH 6

void Trier(int Tab[], int NbElts) {
    for (int i = NbElts - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (Tab[j + 1] < Tab[j]) {
                int temp = Tab[j + 1];
                Tab[j + 1] = Tab[j];
                Tab[j] = temp;
            }
        }
    }
}

void Aff(int Tab[], int NbElts) {
    for (int i = 0; i < NbElts; i++) printf("%d ", Tab[i]);
    printf("\n");
}

void TrierPtr(int *Tab, int NbElts, int **TabP) {
    for (int i = 0; i < NbElts; i++)
        TabP[i] = &Tab[i];

    for (int i = 0; i < NbElts - 1; i++) {
        for (int j = i + 1; j < NbElts; j++) {
            if (*TabP[i] > *TabP[j]) {
                int *tmp = TabP[i];
                TabP[i] = TabP[j];
                TabP[j] = tmp;
            }
        }
    }
}

int** TrierPtr2(int *Tab, int NbElts){
    int ** TabP = malloc(NbElts*sizeof(int *));
    TrierPtr(Tab,NbElts,TabP);
    return TabP;
}

void TrierPtr3(int *Tab, int NbElts, int ***TabP){
    *TabP = malloc(NbElts*sizeof(int *));
    TrierPtr(Tab,NbElts,*TabP);
}

void AffPtr(int *TabP[], int NbElts){
    for (int i = 0; i < NbElts; i++) printf("%d ", *TabP[i]);
    printf("\n");
}

int main(void) {
    int tab[LENGTH] = {0, 3, 5, 2, 6, 7};

    Aff(tab, LENGTH);
    printf("Aff1\n");
    Trier(tab, LENGTH);
    Aff(tab, LENGTH);
    printf("Aff2\n");


    int Tableau[LENGTH]={3,1,2,5,6,7};
    int *TableauP[LENGTH];
    int **Tabl;
    TrierPtr(Tableau,LENGTH,TableauP);
    AffPtr(TableauP, LENGTH);
    printf("Aff3\n");
    int** TablP = TrierPtr2(Tableau,LENGTH);
    AffPtr(TablP, LENGTH);
    printf("Aff4\n");
    TrierPtr3(Tableau,LENGTH,&Tabl);
    AffPtr(Tabl, LENGTH);
    printf("Aff5\n");


    free(TablP);
    free(Tabl);

    return 0;
}
