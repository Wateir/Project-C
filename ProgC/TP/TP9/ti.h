#ifndef __TI_H__
#define __TI_H__
#include "image.h"

#define GRIS_MAX 256

extern tImage Rotation(tImage Im);

extern tImage AppliquerTable(unsigned char Table[GRIS_MAX], tImage Im);

extern void RemplirTableInversion(unsigned char Table[GRIS_MAX]);

extern void RemplirTableGamma(double Gamma, unsigned char Table[GRIS_MAX]);

#endif
