#ifndef KISI_H
#define KISI_H

typedef struct Kisi {
    char* isim;
    int yas;
    double kalanOmur; // saat cinsinden
    char* uzayAraciAdi;

    void (*yaslan)(struct Kisi* self, double katsayi); // Gezegen'e göre
    int (*olduMu)(struct Kisi* self); // 1 = öldü, 0 = yaşıyor
} Kisi;

Kisi* KisiOlustur(const char* isim, int yas, double kalanOmur, const char* uzayAraciAdi);
void KisiYokEt(Kisi* kisi);

#endif
