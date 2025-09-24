#ifndef CUCE_GEZEGEN_H
#define CUCE_GEZEGEN_H

#include "Gezegen.h"

typedef struct {
    Gezegen base;
} CuceGezegen;

CuceGezegen* CuceGezegenOlustur(const char* isim, int gununSaatSayisi, int gun, int ay, int yil);
void CuceGezegenYokEt(CuceGezegen*);

#endif
