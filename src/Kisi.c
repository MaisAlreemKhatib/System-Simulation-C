#include <stdlib.h>
#include <string.h>
#include "../include/Kisi.h"

static void yaslan(struct Kisi* self, double katsayi) {
    self->kalanOmur -= katsayi;
    if (self->kalanOmur < 0) self->kalanOmur = 0;
}

static int olduMu(struct Kisi* self) {
    return self->kalanOmur <= 0;
}

Kisi* KisiOlustur(const char* isim, int yas, double kalanOmur, const char* uzayAraciAdi) {
    Kisi* k = (Kisi*)malloc(sizeof(Kisi));
    k->isim = strdup(isim);
    k->yas = yas;
    k->kalanOmur = kalanOmur;
    k->uzayAraciAdi = strdup(uzayAraciAdi);

    k->yaslan = yaslan;
    k->olduMu = olduMu;

    return k;
}

void KisiYokEt(Kisi* k) {
    if (k) {
        free(k->isim);
        free(k->uzayAraciAdi);
        free(k);
    }
}
