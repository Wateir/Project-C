#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    for (int i= 0; i<argc;i++){
        int j =0;
        while(argv[i][j] != '\0'){
            write(1,&argv[i][j],1);
            j++;
        }
        write(1,"\n",1);
    }
    exit(0);
}
