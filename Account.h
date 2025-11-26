#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
protected:
    std::string hesapNo;
    std::string hesapSahibi;
    double bakiye;
    std::string hesapTipi;

public:
    Account(const std::string& hesapNo, const std::string& hesapSahibi, double bakiye = 0.0);
    virtual ~Account() {}

    virtual bool paraYatir(double miktar);
    virtual bool paraCek(double miktar);
    double bakiyeSorgula() const;
    
    std::string getHesapNo() const;
    std::string getHesapSahibi() const;
    std::string getHesapTipi() const;
    
    virtual std::string dosyayaYaz() const;
    static Account* dosyadanOku(const std::string& satir);
    
    virtual void hesapBilgileriniGoster() const;
};

#endif

