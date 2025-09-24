#ifndef SIMULASYON_H
#define SIMULASYON_H

#include "Kisi.h"
#include "UzayAraci.h"
#include "Gezegen.h"

void SimulasyonuBaslat(Kisi** kisiler, int kisiSayisi,
                        UzayAraci** araclar, int aracSayisi,
                        Gezegen** gezegenler, int gezegenSayisi);

#endif
