#ifndef BUZ_DEVI_GEZEGEN_H
#define BUZ_DEVI_GEZEGEN_H

#include "Gezegen.h"

typedef struct {
    Gezegen base;
} BuzDeviGezegen;

BuzDeviGezegen* BuzDeviGezegenOlustur(const char* isim, int gununSaatSayisi, int gun, int ay, int yil);
void BuzDeviGezegenYokEt(BuzDeviGezegen*);

#endif
