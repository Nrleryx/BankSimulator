#include "VadeliHesap.h"
#include <iostream>

VadeliHesap::VadeliHesap(const std::string& hesapNo, const std::string& hesapSahibi, double bakiye, int vadeGunu) 
    : Account(hesapNo, hesapSahibi, bakiye), vadeGunu(vadeGunu) {
    hesapTipi = "Vadeli";
}

bool VadeliHesap::paraCek(double miktar) {
    if (miktar > 0 && miktar <= bakiye) {
        bakiye -= miktar;
        return true;
    }
    return false;
}

