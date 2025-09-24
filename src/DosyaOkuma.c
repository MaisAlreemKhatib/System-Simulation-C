#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/DosyaOkuma.h"
#include "../include/KayacGezegen.h"
#include "../include/GazDeviGezegen.h"
#include "../include/BuzDeviGezegen.h"
#include "../include/CuceGezegen.h"

int KisiDosyasiniOku(const char* dosyaAdi, Kisi*** kisiler, int* kisiSayisi) {
    FILE* f = fopen(dosyaAdi, "r");
    if (!f) return 0;

    int kapasite = 10;
    *kisiler = malloc(sizeof(Kisi*) * kapasite);
    *kisiSayisi = 0;

    char satir[256];
    while (fgets(satir, sizeof(satir), f)) {
        char* isim = strtok(satir, "#");
        int yas = atoi(strtok(NULL, "#"));
        double omur = atof(strtok(NULL, "#"));
        char* araci = strtok(NULL, "#\n");

        if (*kisiSayisi >= kapasite) {
            kapasite *= 2;
            *kisiler = realloc(*kisiler, sizeof(Kisi*) * kapasite);
        }
        (*kisiler)[(*kisiSayisi)++] = KisiOlustur(isim, yas, omur, araci);
    }


    
    fclose(f);
    return 1;
}

int AracDosyasiniOku(const char* dosyaAdi, UzayAraci*** araclar, int* aracSayisi) {
    FILE* f = fopen(dosyaAdi, "r");
    if (!f) return 0;

    int kapasite = 10;
    *araclar = malloc(sizeof(UzayAraci*) * kapasite);
    *aracSayisi = 0;

    char satir[256];
    while (fgets(satir, sizeof(satir), f)) {
        char* isim = strtok(satir, "#");
        char* cikis = strtok(NULL, "#");
        char* varis = strtok(NULL, "#");
        char* tarih = strtok(NULL, "#");
        int mesafe = atoi(strtok(NULL, "#\n"));

        int gun, ay, yil;
        sscanf(tarih, "%d.%d.%d", &gun, &ay, &yil);

        if (*aracSayisi >= kapasite) {
            kapasite *= 2;
            *araclar = realloc(*araclar, sizeof(UzayAraci*) * kapasite);
        }
        UzayAraci* arac = UzayAraciOlustur(isim, cikis, varis, gun, ay, yil, mesafe);
arac->hedefeKalanSaat = arac->mesafeSaat;  // <<< Kritik düzeltme
(*araclar)[(*aracSayisi)++] = arac;

    }

    fclose(f);
    return 1;
}

int GezegenDosyasiniOku(const char* dosyaAdi, Gezegen*** gezegenler, int* gezegenSayisi) {
    FILE* f = fopen(dosyaAdi, "r");
    if (!f) return 0;

    int kapasite = 10;
    *gezegenler = malloc(sizeof(Gezegen*) * kapasite);
    *gezegenSayisi = 0;

    char satir[256];
    while (fgets(satir, sizeof(satir), f)) {
        char* isim = strtok(satir, "#");
        int tur = atoi(strtok(NULL, "#"));
        int gunSaat = atoi(strtok(NULL, "#"));
        char* tarih = strtok(NULL, "#\n");

        int gun, ay, yil;
        sscanf(tarih, "%d.%d.%d", &gun, &ay, &yil);

        Gezegen* g = NULL;
        switch (tur) {
            case 0: g = (Gezegen*)KayacGezegenOlustur(isim, gunSaat, gun, ay, yil); break;
            case 1: g = (Gezegen*)GazDeviGezegenOlustur(isim, gunSaat, gun, ay, yil); break;
            case 2: g = (Gezegen*)BuzDeviGezegenOlustur(isim, gunSaat, gun, ay, yil); break;
            case 3: g = (Gezegen*)CuceGezegenOlustur(isim, gunSaat, gun, ay, yil); break;
        }

        if (*gezegenSayisi >= kapasite) {
            kapasite *= 2;
            *gezegenler = realloc(*gezegenler, sizeof(Gezegen*) * kapasite);
        }

        (*gezegenler)[(*gezegenSayisi)++] = g;
    }

    fclose(f);
    return 1;
}
