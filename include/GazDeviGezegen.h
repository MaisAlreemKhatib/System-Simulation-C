#ifndef GAZ_DEVI_GEZEGEN_H
#define GAZ_DEVI_GEZEGEN_H

#include "Gezegen.h"

typedef struct {
    Gezegen base;
} GazDeviGezegen;

GazDeviGezegen* GazDeviGezegenOlustur(const char* isim, int gununSaatSayisi, int gun, int ay, int yil);
void GazDeviGezegenYokEt(GazDeviGezegen*);

#endif
