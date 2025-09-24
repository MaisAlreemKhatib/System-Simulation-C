#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Gezegen.h"

// Zaman güncelleme fonksiyonu (tüm gezegenler ortak kullanacak)
void Gezegen_ZamanGuncelle(Gezegen* this) {
    this->saat++;
    if (this->saat >= this->gunSaatSayisi) {
        this->saat = 0;
        this->gun++;
        int sinir = 31;
        if (this->ay == 2) sinir = 28;
        else if (this->ay == 4 || this->ay == 6 || this->ay == 9 || this->ay == 11) sinir = 30;
        if (this->gun > sinir) {
            this->gun = 1;
            this->ay++;
            if (this->ay > 12) {
                this->ay = 1;
                this->yil++;
            }
        }
    }
}

Gezegen* GezegenOlustur(const char* isim, int tur, int gunSaatSayisi, int gun, int ay, int yil) {
    Gezegen* g = (Gezegen*)malloc(sizeof(Gezegen));
    g->isim = strdup(isim);
    g->tur = tur;
    g->gunSaatSayisi = gunSaatSayisi;
    g->gun = gun;
    g->ay = ay;
    g->yil = yil;
    g->saat = 0;

    // Fonksiyon pointerlarını ata
    g->zamanGuncelle = Gezegen_ZamanGuncelle;
    g->yaslanmaKatsayisiAl = NULL; // Her tür gezegen kendi dosyasında bunu tanımlar

    return g;
}

void GezegenYokEt(Gezegen* g) {
    if (g) {
        free(g->isim);
        free(g);
    }
}
