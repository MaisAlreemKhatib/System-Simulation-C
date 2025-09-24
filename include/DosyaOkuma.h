#ifndef DOSYA_OKUMA_H
#define DOSYA_OKUMA_H

#include "Kisi.h"
#include "UzayAraci.h"
#include "Gezegen.h"

// Kişi listesi
int KisiDosyasiniOku(const char* dosyaAdi, Kisi*** kisiler, int* kisiSayisi);

// Uzay aracı listesi
int AracDosyasiniOku(const char* dosyaAdi, UzayAraci*** araclar, int* aracSayisi);

// Gezegen listesi (soyut yapıdan türetilmiş dizi dönecek)
int GezegenDosyasiniOku(const char* dosyaAdi, Gezegen*** gezegenler, int* gezegenSayisi);

#endif
