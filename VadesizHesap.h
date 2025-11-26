#ifndef VADESIZ_HESAP_H
#define VADESIZ_HESAP_H

#include "Account.h"

class VadesizHesap : public Account {
public:
    VadesizHesap(const std::string& hesapNo, const std::string& hesapSahibi, double bakiye = 0.0);
    bool paraCek(double miktar) override;
};

#endif

