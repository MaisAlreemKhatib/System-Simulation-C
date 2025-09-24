#ifndef GEZEGEN_H
#define GEZEGEN_H

typedef struct Gezegen {
    char* isim;
    int tur;
    int gunSaatSayisi;
    int gun;
    int ay;
    int yil;
    int saat; 

    void (*zamanGuncelle)(struct Gezegen*);
    double (*yaslanmaKatsayisiAl)(struct Gezegen*);
} Gezegen;

Gezegen* GezegenOlustur(const char* isim, int tur, int gunSaatSayisi, int gun, int ay, int yil);
void GezegenYokEt(Gezegen*);

#endif
