#include "Account.h"
#include "VadesizHesap.h"
#include "VadeliHesap.h"
#include <iostream>
#include <sstream>

Account::Account(const std::string& hesapNo, const std::string& hesapSahibi, double bakiye) 
    : hesapNo(hesapNo), hesapSahibi(hesapSahibi), bakiye(bakiye), hesapTipi("Vadesiz") {
}

bool Account::paraYatir(double miktar) {
    if (miktar > 0) {
        bakiye += miktar;
        return true;
    }
    return false;
}

bool Account::paraCek(double miktar) {
    if (miktar > 0 && miktar <= bakiye) {
        bakiye -= miktar;
        return true;
    }
    return false;
}

double Account::bakiyeSorgula() const {
    return bakiye;
}

std::string Account::getHesapNo() const {
    return hesapNo;
}

std::string Account::getHesapSahibi() const {
    return hesapSahibi;
}

std::string Account::getHesapTipi() const {
    return hesapTipi;
}

std::string Account::dosyayaYaz() const {
    std::ostringstream oss;
    oss << hesapNo << "|" << hesapSahibi << "|" << hesapTipi << "|" << bakiye;
    return oss.str();
}

Account* Account::dosyadanOku(const std::string& satir) {
    std::istringstream iss(satir);
    std::string hesapNo, hesapSahibi, hesapTipi, bakiyeStr;
    
    std::getline(iss, hesapNo, '|');
    std::getline(iss, hesapSahibi, '|');
    std::getline(iss, hesapTipi, '|');
    std::getline(iss, bakiyeStr, '|');
    
    double bakiye = std::stod(bakiyeStr);
    
    if (hesapTipi == "Vadeli") {
        return new VadeliHesap(hesapNo, hesapSahibi, bakiye);
    } else {
        return new VadesizHesap(hesapNo, hesapSahibi, bakiye);
    }
}

void Account::hesapBilgileriniGoster() const {
    std::cout << "Hesap No: " << hesapNo << std::endl;
    std::cout << "Sahip: " << hesapSahibi << std::endl;
    std::cout << "Tip: " << hesapTipi << std::endl;
    std::cout << "Bakiye: " << bakiye << " TL" << std::endl;
}

