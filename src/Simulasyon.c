#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "../include/Simulasyon.h"

static void EkraniTemizle() {
#ifdef _WIN32
    system("cls");  // Windows için ekranı temizler
#else
    system("clear");  // Unix tabanlı sistemler için ekranı temizler
#endif
}

static int TarihToToplamSaat(int gun, int ay, int yil, int saat, int gunSaatSayisi) {
    return (((yil * 12 + ay) * 31 + gun) * gunSaatSayisi) + saat;
}



static void GezegenDurumunuYaz(Gezegen** gezegenler, int gezegenSayisi, UzayAraci** araclar, int aracSayisi, Kisi** kisiler, int kisiSayisi) {
    printf("Gezegenler:\n");
    printf("           ");
    for (int i = 0; i < gezegenSayisi; i++) {
        printf(" ---%-10s", gezegenler[i]->isim);
    }
    printf("\n");

    printf("Tarih       ");
    for (int i = 0; i < gezegenSayisi; i++) {
        printf("%02d.%02d.%04d    ", gezegenler[i]->gun, gezegenler[i]->ay, gezegenler[i]->yil, gezegenler[i]->saat);
    }
    printf("\n");

    printf("Nufus      ");
    for (int i = 0; i < gezegenSayisi; i++) {
        int nufus = 0;
        for (int j = 0; j < kisiSayisi; j++) {
            Kisi* k = kisiler[j];
            if (!k->olduMu(k) && k->uzayAraciAdi != NULL) {
                for (int m = 0; m < aracSayisi; m++) {
                    UzayAraci* a = araclar[m];
                   // a->hedefeKalanSaat = a->mesafeSaat;
                    if (strcmp(a->isim, k->uzayAraciAdi) == 0) {
                        if (a->hedefeKalanSaat == 0 && strcmp(a->varisGezegeni, gezegenler[i]->isim) == 0)
                            nufus++;
                        else if (a->hedefeKalanSaat > 0 && strcmp(a->cikisGezegeni, gezegenler[i]->isim) == 0)
                            nufus++;
                    }
                }
            }
        }
        printf(" %-13d", nufus);
    }
    printf("\n\n");
}

void AracDurumunuYaz(UzayAraci** araclar, int aracSayisi, Gezegen** gezegenler, int gezegenSayisi) {
    printf("Uzay Araclari:\n");
    printf("Arac Adi | Durum    | Cikis | Varis | Hedefe Kalan Saat  | Hedefe Varacagi Tarih\n");

    for (int i = 0; i < aracSayisi; i++) {
        UzayAraci* a = araclar[i];
        const char* durum;

        if (a->imhaDurumu) {
            durum = "IMHA";
        } else if (a->hedefeKalanSaat == 0) {
            durum = "Vardi";
        } else if (a->hedefeKalanSaat < a->mesafeSaat) {
            durum = "Yolda";
        } else {
            durum = "Bekliyor";
        }

        printf("%-8s | %-8s | %-5s | %-5s | ", a->isim, durum, a->cikisGezegeni, a->varisGezegeni);

        if (a->imhaDurumu) {
            printf("--                 | --\n");
        } else {
            printf("%-18d | ", a->hedefeKalanSaat);

            int gun = a->cikisGun;
            int ay = a->cikisAy;
            int yil = a->cikisYil;
            int saat = 0;
            int kalan = a->mesafeSaat;
            int hedefSaat = 24;

            for (int g = 0; g < gezegenSayisi; g++) {
                if (strcmp(a->varisGezegeni, gezegenler[g]->isim) == 0) {
                    hedefSaat = gezegenler[g]->gunSaatSayisi;
                    break;
                }
            }

            while (kalan--) {
                saat++;
                if (saat >= hedefSaat) {
                    saat = 0;
                    gun++;
                    int sinir = 31;
                    if (ay == 2) sinir = 28;
                    else if (ay == 4 || ay == 6 || ay == 9 || ay == 11) sinir = 30;
                    if (gun > sinir) {
                        gun = 1;
                        ay++;
                        if (ay > 12) {
                            ay = 1;
                            yil++;
                        }
                    }
                }
            }

            printf("%02d.%02d.%04d\n", gun, ay, yil);
        }
    }
}


void SimulasyonuBaslat(Kisi** kisiler, int kisiSayisi, UzayAraci** araclar, int aracSayisi, Gezegen** gezegenler, int gezegenSayisi) {
    while (1) {
        int bittiMi = 1;
        for (int i = 0; i < aracSayisi; i++) {
            if (!araclar[i]->imhaDurumu && araclar[i]->hedefeKalanSaat > 0) {
                bittiMi = 0;
                break;
            }
        }

        if (bittiMi) break;  // Tüm araçlar hedeflerine ulaşmışsa, simülasyon durur.

        EkraniTemizle();  // Ekranı temizle

        // 1. Durumları yazdır
        GezegenDurumunuYaz(gezegenler, gezegenSayisi, araclar, aracSayisi, kisiler, kisiSayisi);
        AracDurumunuYaz(araclar, aracSayisi, gezegenler, gezegenSayisi);

        //  2. Gezegenlerin zamanını güncelle
        for (int i = 0; i < gezegenSayisi; i++) {
            gezegenler[i]->zamanGuncelle(gezegenler[i]);
        }

        // 3. Yolcuları yaşlandır
        for (int i = 0; i < kisiSayisi; i++) {
            Kisi* k = kisiler[i];
            if (k->olduMu(k)) continue;

            for (int j = 0; j < aracSayisi; j++) {
                UzayAraci* a = araclar[j];
               // a->hedefeKalanSaat = a->mesafeSaat;
                if (strcmp(a->isim, k->uzayAraciAdi) == 0) {
                    if (a->aktifMi && a->hedefeKalanSaat > 0) {
                        k->yaslan(k, 1.0);
                    } else {
                        for (int g = 0; g < gezegenSayisi; g++) {
                            if (strcmp(gezegenler[g]->isim, a->varisGezegeni) == 0) {
                                double oran = gezegenler[g]->yaslanmaKatsayisiAl(gezegenler[g]);
                                k->yaslan(k, oran);
                                break;
                            }
                        }
                    }
                    break;
                }
            }
        }

        // 4. Uzay araçlarının zamanını ilerlet
        for (int i = 0; i < aracSayisi; i++) {
            if (!araclar[i]->aktifMi) {
                for (int g = 0; g < gezegenSayisi; g++) {
                    if (strcmp(araclar[i]->cikisGezegeni, gezegenler[g]->isim) == 0) {
                        
                        int gezegenZaman = TarihToToplamSaat(
    gezegenler[g]->gun, gezegenler[g]->ay, gezegenler[g]->yil,
    gezegenler[g]->saat, gezegenler[g]->gunSaatSayisi);

int cikisZaman = TarihToToplamSaat(
    araclar[i]->cikisGun, araclar[i]->cikisAy, araclar[i]->cikisYil,
    0, gezegenler[g]->gunSaatSayisi);


                        if (gezegenZaman >= cikisZaman) {
                            araclar[i]->aktifMi = 1;
                        }
                        break;
                    }
                }
            }

            araclar[i]->saatIlerle(araclar[i]);
            araclar[i]->durumGuncelle(araclar[i]);
        }

        
    }

    EkraniTemizle();
    printf("Simulasyon tamamlandi.\n\n");
    printf("Tum uzay araclari hedeflerine ulasti. Simulasyon basariyla sona erdi.\n\n");

    // Final durumu yazdır
    GezegenDurumunuYaz(gezegenler, gezegenSayisi, araclar, aracSayisi, kisiler, kisiSayisi);
    AracDurumunuYaz(araclar, aracSayisi, gezegenler, gezegenSayisi);
}
