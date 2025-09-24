#ifndef ZAMAN_H
#define ZAMAN_H

typedef struct {
    int gun;
    int ay;
    int yil;
    int saat;
} Zaman;

Zaman* ZamanOlustur(int gun, int ay, int yil);
void ZamanYokEt(Zaman* z);

// Zaman işlemleri
void ZamanSaatIlerle(Zaman* z, int saatAdedi); // Belirli saat kadar ilerletir
int ZamanKarsilastir(Zaman* a, Zaman* b);      // -1: a < b, 0: eşit, 1: a > b
int ZamanFarkSaat(Zaman* a, Zaman* b);         // a - b saat cinsinden fark

#endif
