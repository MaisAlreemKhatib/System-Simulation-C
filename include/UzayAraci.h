#ifndef UZAY_ARACI_H
#define UZAY_ARACI_H

#include "Kisi.h"

typedef struct UzayAraci {
    char* isim;
    char* cikisGezegeni;
    char* varisGezegeni;
    int cikisGun, cikisAy, cikisYil;
    int mesafeSaat;
    int hedefeKalanSaat;

    int imhaDurumu;
    int aktifMi;
    Kisi** yolcular;
    int yolcuSayisi;
    int kapasite;

    void (*saatIlerle)(struct UzayAraci*);
    void (*yolcuEkle)(struct UzayAraci*, Kisi*);
    void (*durumGuncelle)(struct UzayAraci*);
} UzayAraci;

UzayAraci* UzayAraciOlustur(const char* isim, const char* cikis, const char* varis,
                            int gun, int ay, int yil, int mesafeSaat);
void UzayAraciYokEt(UzayAraci* araci);

#endif
