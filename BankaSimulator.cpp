#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Account.h"
#include "VadesizHesap.h"
#include "VadeliHesap.h"

using namespace std;

const string DOSYA_ADI = "hesaplar.txt";

void menuGoster() {
    cout << "\n=== BANKa HESAP SIMULATORU ===" << endl;
    cout << "1. Yeni hesap ac" << endl;
    cout << "2. Para yatir" << endl;
    cout << "3. Para cek" << endl;
    cout << "4. Bakiye sorgula" << endl;
    cout << "5. Tum hesaplari goster" << endl;
    cout << "6. Hesap sil" << endl;
    cout << "7. Dosyaya kaydet" << endl;
    cout << "8. Dosyadan yukle" << endl;
    cout << "0. Cikis" << endl;
    cout << "Seciminiz: ";
}

Account* hesapOlustur() {
    string hesapNo, hesapSahibi;
    int tip;
    double bakiye;
    
    cout << "Hesap No: ";
    cin >> hesapNo;
    cout << "Hesap Sahibi: ";
    cin.ignore();
    getline(cin, hesapSahibi);
    cout << "Baslangic bakiyesi: ";
    cin >> bakiye;
    cout << "Hesap tipi (1-Vadesiz, 2-Vadeli): ";
    cin >> tip;
    
    if (tip == 2) {
        int vade;
        cout << "Vade gunu: ";
        cin >> vade;
        return new VadeliHesap(hesapNo, hesapSahibi, bakiye, vade);
    } else {
        return new VadesizHesap(hesapNo, hesapSahibi, bakiye);
    }
}

void dosyayaKaydet(const vector<Account*>& hesaplar) {
    ofstream dosya(DOSYA_ADI);
    if (!dosya.is_open()) {
        cout << "Dosya acilamadi!" << endl;
        return;
    }
    
    for (const auto& hesap : hesaplar) {
        dosya << hesap->dosyayaYaz() << endl;
    }
    
    dosya.close();
    cout << "Hesaplar kaydedildi." << endl;
}

vector<Account*> dosyadanYukle() {
    vector<Account*> hesaplar;
    ifstream dosya(DOSYA_ADI);
    
    if (!dosya.is_open()) {
        cout << "Dosya bulunamadi veya acilamadi." << endl;
        return hesaplar;
    }
    
    string satir;
    while (getline(dosya, satir)) {
        if (!satir.empty()) {
            Account* hesap = Account::dosyadanOku(satir);
            if (hesap != nullptr) {
                hesaplar.push_back(hesap);
            }
        }
    }
    
    dosya.close();
    cout << hesaplar.size() << " hesap yuklendi." << endl;
    return hesaplar;
}

Account* hesapBul(const vector<Account*>& hesaplar, const string& hesapNo) {
    for (auto hesap : hesaplar) {
        if (hesap->getHesapNo() == hesapNo) {
            return hesap;
        }
    }
    return nullptr;
}

int main() {
    vector<Account*> hesaplar;
    int secim;
    
    hesaplar = dosyadanYukle();
    
    do {
        menuGoster();
        cin >> secim;
        
        switch(secim) {
            case 1: {
                Account* yeniHesap = hesapOlustur();
                hesaplar.push_back(yeniHesap);
                cout << "Hesap olusturuldu!" << endl;
                break;
            }
            case 2: {
                string hesapNo;
                double miktar;
                cout << "Hesap No: ";
                cin >> hesapNo;
                cout << "Yatirilacak miktar: ";
                cin >> miktar;
                
                Account* hesap = hesapBul(hesaplar, hesapNo);
                if (hesap != nullptr) {
                    if (hesap->paraYatir(miktar)) {
                        cout << "Para yatirildi. Yeni bakiye: " << hesap->bakiyeSorgula() << " TL" << endl;
                    } else {
                        cout << "Gecersiz miktar!" << endl;
                    }
                } else {
                    cout << "Hesap bulunamadi!" << endl;
                }
                break;
            }
            case 3: {
                string hesapNo;
                double miktar;
                cout << "Hesap No: ";
                cin >> hesapNo;
                cout << "Cekilecek miktar: ";
                cin >> miktar;
                
                Account* hesap = hesapBul(hesaplar, hesapNo);
                if (hesap != nullptr) {
                    if (hesap->paraCek(miktar)) {
                        cout << "Para cekildi. Kalan bakiye: " << hesap->bakiyeSorgula() << " TL" << endl;
                    } else {
                        cout << "Yetersiz bakiye veya gecersiz miktar!" << endl;
                    }
                } else {
                    cout << "Hesap bulunamadi!" << endl;
                }
                break;
            }
            case 4: {
                string hesapNo;
                cout << "Hesap No: ";
                cin >> hesapNo;
                
                Account* hesap = hesapBul(hesaplar, hesapNo);
                if (hesap != nullptr) {
                    hesap->hesapBilgileriniGoster();
                } else {
                    cout << "Hesap bulunamadi!" << endl;
                }
                break;
            }
            case 5: {
                if (hesaplar.empty()) {
                    cout << "Hesap yok!" << endl;
                } else {
                    for (const auto& hesap : hesaplar) {
                        hesap->hesapBilgileriniGoster();
                        cout << "---" << endl;
                    }
                }
                break;
            }
            case 6: {
                string hesapNo;
                cout << "Silinecek hesap No: ";
                cin >> hesapNo;
                
                for (auto it = hesaplar.begin(); it != hesaplar.end(); ++it) {
                    if ((*it)->getHesapNo() == hesapNo) {
                        delete *it;
                        hesaplar.erase(it);
                        cout << "Hesap silindi." << endl;
                        break;
                    }
                }
                break;
            }
            case 7: {
                dosyayaKaydet(hesaplar);
                break;
            }
            case 8: {
                for (auto hesap : hesaplar) {
                    delete hesap;
                }
                hesaplar.clear();
                hesaplar = dosyadanYukle();
                break;
            }
            case 0:
                cout << "Cikiliyor..." << endl;
                break;
            default:
                cout << "Gecersiz secim!" << endl;
        }
    } while (secim != 0);
    
    dosyayaKaydet(hesaplar);
    
    for (auto hesap : hesaplar) {
        delete hesap;
    }
    
    return 0;
}

