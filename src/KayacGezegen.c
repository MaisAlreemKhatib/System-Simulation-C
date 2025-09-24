#include <stdlib.h>
#include <string.h>
#include "../include/KayacGezegen.h"

static void zamanGuncelle(Gezegen* self) {
    self->saat++;
    if (self->saat >= self->gunSaatSayisi) {
        self->saat = 0;
        self->gun++;

        int gun_sinir;
        switch (self->ay) {
            case 2: gun_sinir = 28; break;
            case 4: case 6: case 9: case 11: gun_sinir = 30; break;
            default: gun_sinir = 31;
        }

        if (self->gun > gun_sinir) {
            self->gun = 1;
            self->ay++;
            if (self->ay > 12) {
                self->ay = 1;
                self->yil++;
            }
        }
    }
}

static double yaslanmaKatsayisiAl(Gezegen* self) {
    return 1.0;
}

KayacGezegen* KayacGezegenOlustur(const char* isim, int gunSaatSayisi, int gun, int ay, int yil) {
    KayacGezegen* kg = (KayacGezegen*)malloc(sizeof(KayacGezegen));
    Gezegen* g = (Gezegen*)kg;

    g->isim = strdup(isim);
    g->tur = 0;
    g->gunSaatSayisi = gunSaatSayisi;
    g->gun = gun;
    g->ay = ay;
    g->yil = yil;
    g->saat = 0;
    g->zamanGuncelle = zamanGuncelle;
    g->yaslanmaKatsayisiAl = yaslanmaKatsayisiAl;

    return kg;
}

void KayacGezegenYokEt(KayacGezegen* kg) {
    if (kg) {
        free(kg->base.isim);
        free(kg);
    }
}
