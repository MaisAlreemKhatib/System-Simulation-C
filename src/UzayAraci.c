#include <stdlib.h>
#include <string.h>
#include "../include/UzayAraci.h"

#define BASLANGIC_KAPASITE 10

static void saatIlerle(struct UzayAraci* self) {
    if (!self->imhaDurumu && self->hedefeKalanSaat > 0) {
        self->hedefeKalanSaat--;
    }
}

static void yolcuEkle(struct UzayAraci* self, Kisi* kisi) {
    if (self->yolcuSayisi >= self->kapasite) {
        self->kapasite *= 2;
        self->yolcular = realloc(self->yolcular, self->kapasite * sizeof(Kisi*));
    }
    self->yolcular[self->yolcuSayisi++] = kisi;
}

static void durumGuncelle(struct UzayAraci* self) {
    if (!self->aktifMi) return;  // لا تحدّث شيء إذا المركبة ما انطلقت بعد
    if (self->hedefeKalanSaat == 0) return;  // وصلت بنجاح، لا تدمّرها

    int yasayanVar = 0;
    for (int i = 0; i < self->yolcuSayisi; i++) {
        if (!self->yolcular[i]->olduMu(self->yolcular[i])) {
            yasayanVar = 1;
            break;
        }
    }

    if (!yasayanVar) {
        self->imhaDurumu = 1;  // فقط إذا انطلقت وما في ركاب أحياء
    }
}


UzayAraci* UzayAraciOlustur(const char* isim, const char* cikis, const char* varis,
                            int gun, int ay, int yil, int mesafeSaat) {
    UzayAraci* ua = (UzayAraci*)malloc(sizeof(UzayAraci));
    ua->isim = strdup(isim);
    ua->cikisGezegeni = strdup(cikis);
    ua->varisGezegeni = strdup(varis);
    ua->cikisGun = gun;
    ua->cikisAy = ay;
    ua->cikisYil = yil;
    ua->mesafeSaat = mesafeSaat;
    ua->hedefeKalanSaat = mesafeSaat;
    ua->imhaDurumu = 0;

    ua->kapasite = BASLANGIC_KAPASITE;
    ua->yolcular = malloc(sizeof(Kisi*) * ua->kapasite);
    ua->yolcuSayisi = 0;

    ua->saatIlerle = saatIlerle;
    ua->yolcuEkle = yolcuEkle;
    ua->durumGuncelle = durumGuncelle;
    ua->aktifMi = 0;


    return ua;
}

void UzayAraciYokEt(UzayAraci* ua) {
    if (ua) {
        free(ua->isim);
        free(ua->cikisGezegeni);
        free(ua->varisGezegeni);
        free(ua->yolcular);
        free(ua);
    }
}
