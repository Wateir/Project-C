#include <inttypes.h>
#include <stdio.h>
#define MAX_LENGHT 512

int main(void){
    char text[MAX_LENGHT];

    int i = 0;
    scanf("%c",&text[i]);
    while(text[i]!='#'){
        if ((text[i]<'a' || text[i]>'z') && !(text[i]==' ')){
            printf("%c n'est pas un char valide\n",text[i]);
            return 1;
        }
        i++;
        scanf("%c",&text[i]);

    }
    for(int a=0;a< i;a++){
        printf("%c",text[a]);fflush(stdout);
    }
    printf("\n");

    return 0;

}
