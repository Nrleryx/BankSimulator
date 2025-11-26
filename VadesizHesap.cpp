#include "VadesizHesap.h"
#include <iostream>

VadesizHesap::VadesizHesap(const std::string& hesapNo, const std::string& hesapSahibi, double bakiye) 
    : Account(hesapNo, hesapSahibi, bakiye) {
    hesapTipi = "Vadesiz";
}

bool VadesizHesap::paraCek(double miktar) {
    if (miktar > 0 && miktar <= bakiye) {
        bakiye -= miktar;
        return true;
    }
    return false;
}

