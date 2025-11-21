#include "sf.h"
#include "test_sf_v2.h"

int TestCreerSF(tSF adresse[]){
    for (int i = 0;i<NOMBRE_SF_TEST;i++){
        adresse[i] = CreerSF("nvme0");
    }
    return 0;
}

int TestDetruireSF(tSF adresse[]){
    for (int i = 0;i<NOMBRE_SF_TEST;i++){
        DetruireSF(&adresse[i]);
    }
    return 0;
}

int TestAfficherSF(void){
    tSF sf = CreerSF("nvme");
    AfficherSF(sf);
    DetruireSF(&sf);
    return 0;
}
