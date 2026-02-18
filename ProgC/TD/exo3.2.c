#include <stdio.h>

#define N 3

int main(void){
    int M[N][N]= {{1,2,3},{4,5,6},{7,8,9}};
    int v[N] = {1,2,3};
    int r[N] = {0};

    for(int i=0;i <N;i++){
        for(int j=0;j<N;i++){
            r[i] += M[i][j] * v[i];
        }
    }

    for(int i=0;i < N;i++){
        printf("r[%d] = %d\n",i,r[i]);
    }

}
