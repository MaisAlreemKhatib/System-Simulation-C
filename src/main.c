#include "../include/Simulasyon.h"
#include "../include/DosyaOkuma.h"

int main() {
    Kisi** kisiler; int kisiSayisi;
    UzayAraci** araclar; int aracSayisi;
    Gezegen** gezegenler; int gezegenSayisi;

    KisiDosyasiniOku("Kisiler.txt", &kisiler, &kisiSayisi);
    AracDosyasiniOku("Araclar.txt", &araclar, &aracSayisi);
    GezegenDosyasiniOku("Gezegenler.txt", &gezegenler, &gezegenSayisi);

    SimulasyonuBaslat(kisiler, kisiSayisi, araclar, aracSayisi, gezegenler, gezegenSayisi);
    return 0;
}
