#include "standard.h"

int ReStrcmp(const char ch1[],const char ch2[],const long taillech1){
    for(int i=0;i<taillech1;i++){
        if(ch1[i] != ch2[i]) return 1;
    }
    return 0;
}
