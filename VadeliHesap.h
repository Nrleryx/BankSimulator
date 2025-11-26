#ifndef VADELI_HESAP_H
#define VADELI_HESAP_H

#include "Account.h"

class VadeliHesap : public Account {
private:
    int vadeGunu;

public:
    VadeliHesap(const std::string& hesapNo, const std::string& hesapSahibi, double bakiye = 0.0, int vadeGunu = 30);
    bool paraCek(double miktar) override;
    int getVadeGunu() const { return vadeGunu; }
};

#endif

