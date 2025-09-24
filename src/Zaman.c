#include <stdlib.h>
#include "../include/Zaman.h"

static int gunSayisi(int ay) {
    switch (ay) {
        case 2: return 28;
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
    }
}

Zaman* ZamanOlustur(int gun, int ay, int yil) {
    Zaman* z = (Zaman*)malloc(sizeof(Zaman));
    z->gun = gun;
    z->ay = ay;
    z->yil = yil;
    z->saat = 0;
    return z;
}

void ZamanYokEt(Zaman* z) {
    if (z) free(z);
}

void ZamanSaatIlerle(Zaman* z, int saatAdedi) {
    z->saat += saatAdedi;
    while (z->saat >= 24) {
        z->saat -= 24;
        z->gun++;

        int sinir = gunSayisi(z->ay);
        if (z->gun > sinir) {
            z->gun = 1;
            z->ay++;
            if (z->ay > 12) {
                z->ay = 1;
                z->yil++;
            }
        }
    }
}

int ZamanKarsilastir(Zaman* a, Zaman* b) {
    if (a->yil != b->yil) return a->yil > b->yil ? 1 : -1;
    if (a->ay != b->ay) return a->ay > b->ay ? 1 : -1;
    if (a->gun != b->gun) return a->gun > b->gun ? 1 : -1;
    return 0;
}

// NOT: Bu fonksiyon sadece aynı gezegende kullanılırsa doğru sonuç verir.
int ZamanFarkSaat(Zaman* a, Zaman* b) {
    int toplamA = a->saat + a->gun * 24 + a->ay * 31 * 24 + a->yil * 365 * 24;
    int toplamB = b->saat + b->gun * 24 + b->ay * 31 * 24 + b->yil * 365 * 24;
    return toplamA - toplamB;
}
