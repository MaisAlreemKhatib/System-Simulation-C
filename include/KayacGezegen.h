#ifndef KAYAC_GEZEGEN_H
#define KAYAC_GEZEGEN_H

#include "Gezegen.h"

typedef struct {
    Gezegen base;
} KayacGezegen;

KayacGezegen* KayacGezegenOlustur(const char* isim, int gununSaatSayisi, int gun, int ay, int yil);
void KayacGezegenYokEt(KayacGezegen*);

#endif
