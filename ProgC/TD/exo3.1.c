#include <stdio.h>

#define MAX_SIZE 100
#define CHAR_END '$'

int main(void){
    printf("Taper un text : \n");

    char val[MAX_SIZE];
    scanf("%c",&val[0]);

    int i=0;
    while((val[i]!=CHAR_END)&&(i-1<MAX_SIZE)){
        i++;
        scanf("%c",&val[i]);

    }

    for(int j=i-1;j>=0;j--){
        printf("%c",val[j]);
    }
    printf("\n");

    return 0;
}
