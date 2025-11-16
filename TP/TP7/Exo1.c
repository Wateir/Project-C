#include <stdio.h>
#include <stdlib.h>

typedef unsigned char **tMatrice;

tMatrice MatAllouer(int NbLig, int NbCol){
    tMatrice tab=malloc(NbLig*sizeof(unsigned char*));
    if (tab == NULL) return NULL;

    for (int i =0;i<NbLig;i++){
        tab[i] = malloc(NbCol*sizeof(unsigned char));
        if (tab[i] == NULL) return NULL;
    }
    return tab;
}

void MatLiberer(tMatrice *pMat,int NbLig){
    if (*pMat == NULL) return;
    for (int i =0;i<NbLig;i++){
        free((*pMat)[i]);
    }
    free(*pMat);
    *pMat = NULL;
}

tMatrice Triangle(int n) {
    tMatrice A = MatAllouer(n, n);
    for (int i = 0; i < n; i++) {
        A[i][0] = 1;
        for (int j = 1; j < i; j++) {
            A[i][j] = A[i-1][j-1] + A[i-1][j];
        }
        A[i][i] = 1;
    }
    return A;
}

void AffTriangle(tMatrice A, int n){
    for (int i=0;i<n;i++){
        for (int j=0;j<=i;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
}

int main(void){
    int n;
    printf("Combien de ligne et de colones ? : ");fflush(stdout);
    scanf("%d",&n);
    tMatrice A = Triangle(n);
    AffTriangle(A,n);
    MatLiberer(&A,n);

    return 0;
}
