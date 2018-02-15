#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <conio.h>

using namespace std;

struct Adresat {

    int idAdresat = 0, idUzytkownik = 0;
    string  imieUzytkownik = "", nazwiskoUzytkownik = "", numerTelefonu = "", email = "", adres = "";
};

struct Uzytkownik {

    int idUzytkownik = 0;
    string nazwaUzytkownik = "", hasloUzytkownik = "";
};

bool czyPlikJestPusty() {

    fstream plik("Adresaci.txt", ios::in);
    if(!plik) return 0;
    bool pusty = plik.peek() == EOF;

    return pusty;
}

int dodawanieKontaktu(vector<Adresat> &adresaci, int idUzytkownik, int idOstatniegoAdresataWPliku) {

    system("cls");

    Adresat adresat;

    if(adresaci.empty() == true) {
        adresat.idAdresat = 1;
    } else {
        adresat.idAdresat = idOstatniegoAdresataWPliku + 1;
    }

    cout << "Podaj imie: ";
    cin >> adresat.imieUzytkownik;
    cout << "Podaj nazwisko: ";
    cin >> adresat.nazwiskoUzytkownik;
    cout << "Podaj nr telefonu: ";
    cin.sync();
    getline(cin, adresat.numerTelefonu);
    cout << "Podaj email: ";
    cin >> adresat.email;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, adresat.adres);

    adresat.idUzytkownik = idUzytkownik;

    adresaci.push_back(adresat);

    fstream plik;
    plik.open("Adresaci.txt", ios::out | ios::app);
    if(plik.good()) {

        if(czyPlikJestPusty() == true) {
            plik << adresat.idAdresat << "|" << adresat.idUzytkownik << "|" << adresat.imieUzytkownik << "|" << adresat.nazwiskoUzytkownik << "|" << adresat.numerTelefonu << "|" << adresat.email << "|" << adresat.adres << "|";
        } else {
            plik << endl << adresat.idAdresat << "|" << adresat.idUzytkownik << "|" << adresat.imieUzytkownik << "|" << adresat.nazwiskoUzytkownik << "|" << adresat.numerTelefonu << "|" << adresat.email << "|" << adresat.adres << "|";
        }
        plik.close();

        cout << endl;

        cout << "Adresat zostal dodany do listy kontaktow" << endl;
        Sleep(2000);
        return adresat.idUzytkownik;
    } else
        cout << "Nie mozna otworzyc pliku" << endl;
}

vector<Uzytkownik> rozdzielanieStringowUzytkownicy(vector<Uzytkownik> &uzytkownicy, string wczytanaLinia, char znak) {

    Uzytkownik uzytkownik;

    int numerPojedynczejDanej = 1;
    stringstream ss(wczytanaLinia);
    string pojedynczaDana;

    while(getline(ss, pojedynczaDana, znak)) {

        switch(numerPojedynczejDanej) {
        case 1:
            uzytkownik.idUzytkownik = atoi(pojedynczaDana.c_str());
            break;
        case 2:
            uzytkownik.nazwaUzytkownik = pojedynczaDana;
            break;
        case 3:
            uzytkownik.hasloUzytkownik = pojedynczaDana;
            break;
        }
        numerPojedynczejDanej++;
    }

    uzytkownicy.push_back(uzytkownik);
    return uzytkownicy;
}

void wczytajOsobyZPlikuUzytkownicy(vector<Uzytkownik> &uzytkownicy) {

    string wczytanaLinia;
    fstream plik;

    plik.open("Uzytkownicy.txt", ios::in);

    if(plik.good() == false) {
        cout << "Plik nie istnieje!";
        exit(0);
    }
    while(getline(plik, wczytanaLinia)) {
        uzytkownicy = rozdzielanieStringowUzytkownicy(uzytkownicy, wczytanaLinia, '|');
    }
    plik.close();
}

vector<Adresat> rozdzielanieStringowAdresaci(vector<Adresat> &adresaci, string wczytanaLinia, char znak, int idZalogowanegoUzytkownika) {

    Adresat adresat;

    int numerPojedynczejDanej = 1;
    stringstream ss(wczytanaLinia);
    string pojedynczaDana;

    while(getline(ss, pojedynczaDana, znak)) {

        switch(numerPojedynczejDanej) {
        case 1:
            adresat.idAdresat = atoi(pojedynczaDana.c_str());
            break;
        case 2:
            adresat.idUzytkownik = atoi(pojedynczaDana.c_str());
            break;
        case 3:
            adresat.imieUzytkownik = pojedynczaDana;
            break;
        case 4:
            adresat.nazwiskoUzytkownik = pojedynczaDana;
            break;
        case 5:
            adresat.numerTelefonu = pojedynczaDana;
            break;
        case 6:
            adresat.email = pojedynczaDana;
            break;
        case 7:
            adresat.adres = pojedynczaDana;
            break;
        }
        numerPojedynczejDanej++;
    }

    if(adresat.idUzytkownik == idZalogowanegoUzytkownika) {

        adresaci.push_back(adresat);
    }
    return adresaci;
}

int pobierzIDOstatniegoAdresataWPliku(string daneOstatniegoAdresataWPliku, char znak) {

    string imie, nazwisko, numerTelefonu, email, adres;
    int idUzytkownik, idAdresat;
    int numerPojedynczejDanej = 1;
    stringstream ss(daneOstatniegoAdresataWPliku);
    string pojedynczaDana;

    while(getline(ss, pojedynczaDana, znak)) {

        switch(numerPojedynczejDanej) {
        case 1:
            idAdresat = atoi(pojedynczaDana.c_str());
            break;
        case 2:
            idUzytkownik = atoi(pojedynczaDana.c_str());
            break;
        case 3:
            imie = pojedynczaDana;
            break;
        case 4:
            nazwisko = pojedynczaDana;
            break;
        case 5:
            numerTelefonu = pojedynczaDana;
            break;
        case 6:
            email = pojedynczaDana;
            break;
        case 7:
            adres = pojedynczaDana;
            break;
        }
        numerPojedynczejDanej++;
    }
    return idAdresat;
}

int wczytajOsobyZPlikuAdresaci(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    string wczytanaLinia= "";
    string daneOstatniegoAdresataWPliku = "";
    fstream plik;
    Adresat adresat;
    int idOstaniegoAdresataWPliku = 0;

    plik.open("Adresaci.txt", ios::in);

    if(plik.good() == false) {
        cout << "Plik nie istnieje!";
        exit(0);
    } else {

        while(getline(plik, wczytanaLinia)) {
            adresaci = rozdzielanieStringowAdresaci(adresaci, wczytanaLinia, '|', idZalogowanegoUzytkownika);
        }
        daneOstatniegoAdresataWPliku = wczytanaLinia;

        plik.close();
    }

    if(daneOstatniegoAdresataWPliku != "") {

        idOstaniegoAdresataWPliku = pobierzIDOstatniegoAdresataWPliku(daneOstatniegoAdresataWPliku, '|');
        return idOstaniegoAdresataWPliku;

    } else
        return 0;
}

void rejestracja(vector<Uzytkownik> &uzytkownicy) {

    Uzytkownik uzytkownik;
    string nazwa = "", haslo = "";
    fstream plik;
    unsigned int i = 0;

    wczytajOsobyZPlikuUzytkownicy(uzytkownicy);

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    while(i < uzytkownicy.size()) {

        if(uzytkownicy[i].nazwaUzytkownik == nazwa) {

            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;

    if(uzytkownicy.empty() == true) {
        uzytkownik.idUzytkownik = 1;
    } else {
        uzytkownik.idUzytkownik = uzytkownicy.back().idUzytkownik + 1;
    }

    uzytkownik.nazwaUzytkownik = nazwa;
    uzytkownik.hasloUzytkownik = haslo;

    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if(plik.good()) {
        plik << uzytkownik.idUzytkownik << "|" << uzytkownik.nazwaUzytkownik << "|" << uzytkownik.hasloUzytkownik << "|" << endl;

        plik.close();
        uzytkownicy.push_back(uzytkownik);

        cout << "Uzytkownik zostal dodany" << endl;
        Sleep(2000);
    } else
        cout << "Nie mozna otworzyc pliku" << endl;
}

int logowanie(vector<Uzytkownik> uzytkownicy) {

    Uzytkownik uzytkownik;
    string nazwa = "", haslo = "";
    unsigned int i = 0;
    wczytajOsobyZPlikuUzytkownicy(uzytkownicy);

    if(uzytkownicy.empty() == true) {
        cout << "Brak zarejestrowanych uzytkownikow. Przejdz do rejestracji" << endl;
        Sleep(2000);
        return 0;
    }

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    while(i < uzytkownicy.size()) {

        if(uzytkownicy[i].nazwaUzytkownik == nazwa) {

            for(int proby = 0; proby < 3; proby++) {

                cout << "Podaj haslo. Pozostalo prob: " << 3-proby << ": ";
                cin >> haslo;

                if(uzytkownicy[i].hasloUzytkownik == haslo) {

                    cout << "Zalogowales sie jako " << uzytkownicy[i].nazwaUzytkownik << endl;
                    Sleep(2000);
                    return uzytkownicy[i].idUzytkownik;
                }
            }
            cout << "Podales 3 razy bledne haslo" << endl;
            Sleep(2000);
            return 0;
        } else
            i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(2000);
    return 0;
}

void wyswietlListeKontaktow(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    system("cls");
    vector<Adresat>::iterator itr;

    if(adresaci.empty() == true) {

        cout << "Brak wpisow w ksiazce adresowej" << endl;
        cout << "Jesli chcesz powrocic do menu glownego nacisnij dowolny klawisz" << endl;
        getch();
    }

    else {

        cout << "Spis kontaktow w ksiazce adesowej:" << endl;

        for (itr = adresaci.begin(); itr != adresaci.end(); itr++) {

            if(itr -> idUzytkownik == idZalogowanegoUzytkownika) {

                cout << "Id:                 " << itr -> idAdresat << endl;
                cout << "IdUzytkownik:       " << itr -> idUzytkownik << endl;
                cout << "Imie:               " << itr -> imieUzytkownik << endl;
                cout << "Nazwisko:           " << itr -> nazwiskoUzytkownik << endl;
                cout << "Numer Telefonu:     " << itr -> numerTelefonu << endl;
                cout << "Nr Email:           " << itr -> email << endl;
                cout << "Adres:              " << itr -> adres << endl;
                cout << "-------------------------" << endl;
            }
        }

        cout << "Jesli chcesz powrocic do menu glownego nacisnij dowolny klawisz" << endl;
        getch();
    }
}

void wyszukiwaniePoImieniu(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    system("cls");
    string imie = "";
    int iloscOsob = 0;

    cout << "Wyszukiwanie kontaktow" << endl;
    cout << "Podaj imie: ";
    cin >> imie;

    vector<Adresat>::iterator itr;

    for(itr = adresaci.begin(); itr != adresaci.end(); itr++) {

        if(itr -> idUzytkownik == idZalogowanegoUzytkownika) {

            if(itr -> imieUzytkownik == imie) {

                cout << "Id:                 " << itr -> idAdresat << endl;
                cout << "IdUzytkownik:       " << itr -> idUzytkownik << endl;
                cout << "Imie:               " << itr -> imieUzytkownik << endl;
                cout << "Nazwisko:           " << itr -> nazwiskoUzytkownik << endl;
                cout << "Numer Telefonu:     " << itr -> numerTelefonu << endl;
                cout << "Nr Email:           " << itr -> email << endl;
                cout << "Adres:              " << itr -> adres << endl;
                cout << "-------------------------" << endl;

                iloscOsob++;
            }
        }
    }

    if(iloscOsob == 0) {
        cout << "Kontakt o imieniu " << imie << " nie wystepuje w ksiazce adresowej" << endl;
    }
    cout << endl;

    cout << "Jesli chcesz powrocic do menu glownego nacisnij dowolny klawisz" << endl;
    getch();
}

void wyszukiwaniePoNazwisku(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    system("cls");
    string nazwisko = "";
    int iloscOsob = 0;

    cout << "Wyszukiwanie kontaktow" << endl;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;

    vector<Adresat>::iterator itr;

    for(itr = adresaci.begin(); itr != adresaci.end(); itr++) {

        if(itr -> idUzytkownik == idZalogowanegoUzytkownika) {

            if(itr -> nazwiskoUzytkownik == nazwisko) {

                cout << "Id:                 " << itr -> idAdresat << endl;
                cout << "IdUzytkownik:       " << itr -> idUzytkownik << endl;
                cout << "Imie:               " << itr -> imieUzytkownik << endl;
                cout << "Nazwisko:           " << itr -> nazwiskoUzytkownik << endl;
                cout << "Numer Telefonu:     " << itr -> numerTelefonu << endl;
                cout << "Nr Email:           " << itr -> email << endl;
                cout << "Adres:              " << itr -> adres << endl;
                cout << "-------------------------" << endl;

                iloscOsob++;
            }
        }
    }

    if(iloscOsob == 0) {
        cout << "Kontakt o nazwisku " << nazwisko << " nie wystepuje w ksiazce adresowej" << endl;
    }
    cout << endl;

    cout << "Jesli chcesz powrocic do menu glownego nacisnij dowolny klawisz" << endl;
    getch();
}

void zapiszPlikUzytkownicy(vector<Uzytkownik> &uzytkownicy) {

    ofstream plik;
    plik.open("Uzytkownicy.txt", ios::out);

    for(unsigned int i = 0; i < uzytkownicy.size(); i++) {

        plik << uzytkownicy[i].idUzytkownik << "|" << uzytkownicy[i].nazwaUzytkownik << "|" << uzytkownicy[i].hasloUzytkownik << "|" << endl;
    }
    plik.close();
}

int rozdzielWczytanaLinie(string wczytanaLinia, char znak) {

    int numerPojedynczejDanej = 1;
    int idAdresat;
    stringstream ss(wczytanaLinia);
    string pojedynczaDana = "";

    while(getline(ss, pojedynczaDana, znak)) {

        switch(numerPojedynczejDanej) {
        case 1:
            idAdresat = atoi(pojedynczaDana.c_str());
            break;
        }
        numerPojedynczejDanej++;
    }
    return idAdresat;
}

int zwrocNumerLiniiSzukanegoAdresata(int idEdytowanegoAdresata) {

    fstream plik;
    int numerLinii = 1;
    string wczytanaLinia = "";
    int iD = 0;

    plik.open("Adresaci.txt", ios::in);

    while(getline(plik, wczytanaLinia)) {

        iD = rozdzielWczytanaLinie(wczytanaLinia, '|');

        if(idEdytowanegoAdresata == iD)
            return numerLinii;
        else
            numerLinii++;
    }
    plik.close();
}

string konwersjaIntNaString(Adresat adresat) {

    int i = adresat.idAdresat;
    ostringstream ss;
    ss << i;
    return  ss.str();
}

string konwersjaIntNaStringDruga(Adresat adresat) {

    int i = adresat.idUzytkownik;
    ostringstream ss;
    ss << i;
    return  ss.str();
}

string zmienDaneAdresataNaLiniezDanymiOddzielonePionowaKreska(Adresat adresat) {

    string idUzytkownik= "", idAdresat = "", imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
    string liniaZNowymiDanymiAdresata = "";

    idUzytkownik = konwersjaIntNaString(adresat);
    idAdresat = konwersjaIntNaStringDruga(adresat);
    imie = adresat.imieUzytkownik;
    nazwisko = adresat.nazwiskoUzytkownik;
    numerTelefonu = adresat.numerTelefonu;
    email = adresat.email;
    adres = adresat.adres;

    liniaZNowymiDanymiAdresata = idUzytkownik + "|" + idAdresat + "|" + imie + "|" + nazwisko + "|" + numerTelefonu + "|" + email + "|" + adres + "|";

    return liniaZNowymiDanymiAdresata;
}

void edytujWybranaLinieWPliku(int numerLiniiEdytowanegoAdresata, string liniaZNowymiDanymi) {

    fstream plik,tymczasowy;
    int numerLinii = 1;
    string wczytanaLinia = "";

    plik.open("Adresaci.txt", ios::in);
    tymczasowy.open("Tymczasowy.txt", ios::out | ios::app);

    if(plik.good() == true) {
        while(getline(plik, wczytanaLinia)) {

            if(numerLinii == numerLiniiEdytowanegoAdresata) {
                if(numerLinii == 1) {
                    tymczasowy << liniaZNowymiDanymi;
                } else if(numerLinii > 1) {
                    tymczasowy << endl << liniaZNowymiDanymi;
                }
            } else {
                if(numerLinii == 1) {
                    tymczasowy << wczytanaLinia;
                } else if(numerLinii > 1) {
                    tymczasowy << endl << wczytanaLinia;
                }
            }
            numerLinii++;
        }
        plik.close();
        tymczasowy.close();

        remove("Adresaci.txt");
        rename("Tymczasowy.txt", "Adresaci.txt");
    }
}

void aktualizaujDaneEdytowanegoAdresata(Adresat adresat, int idAdresat) {

    int numerLiniiEdytowanegoAdresata = 0;
    string liniaZDanymi = "";

    numerLiniiEdytowanegoAdresata = zwrocNumerLiniiSzukanegoAdresata(idAdresat);
    liniaZDanymi = zmienDaneAdresataNaLiniezDanymiOddzielonePionowaKreska(adresat);
    edytujWybranaLinieWPliku(numerLiniiEdytowanegoAdresata, liniaZDanymi);
}

bool czyPlikTymczasowyJestPusty() {

    fstream plik("Tymczasowy.txt", ios::in);
    if(!plik) return 0;
    bool pusty = plik.peek() == EOF;

    return pusty;
}

void aktualizaujDanePoUsunieciuAdresata(int idAdresat) {

    fstream plik, tymczasowy;
    int numerLiniiWKtorejJestAdresat = 0;
    int numerLinii = 1;
    string wczytanaLinia = "";

    numerLiniiWKtorejJestAdresat = zwrocNumerLiniiSzukanegoAdresata(idAdresat);

    plik.open("Adresaci.txt", ios::in);
    tymczasowy.open("Tymczasowy.txt", ios::out | ios::app);

    if(plik.good() == true && numerLiniiWKtorejJestAdresat != 0) {

        while(getline(plik, wczytanaLinia)) {
            if(numerLinii == numerLiniiWKtorejJestAdresat) {
                ;
            } else if(numerLinii == 1 && numerLiniiWKtorejJestAdresat != numerLinii) {
                tymczasowy << wczytanaLinia;
            } else if(numerLinii > 1 && numerLiniiWKtorejJestAdresat != 1) {
                tymczasowy << endl << wczytanaLinia;
            } else if(numerLinii == 2 && numerLiniiWKtorejJestAdresat == 1) {
                tymczasowy << wczytanaLinia;
            } else if(numerLinii > 2 && numerLiniiWKtorejJestAdresat == 1) {
                tymczasowy << endl << wczytanaLinia;
            }
            numerLinii++;
        }
        plik.close();
        tymczasowy.close();

        remove("Adresaci.txt");
        rename("Tymczasowy.txt", "Adresaci.txt");
    }
}

void usunKontakt(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    system("cls");

    char wybor, znak;
    bool czyIstniejeAdresat = false;

    int numerKontaktuDoUsuniecia;

    vector<Adresat>::iterator itr;

    if (!adresaci.empty()) {

        cout << "Spis kontaktow w ksiazce adesowej:" << endl;

        for (itr = adresaci.begin(); itr != adresaci.end(); itr++) {

            if (itr -> idUzytkownik == idZalogowanegoUzytkownika) {

                cout << "Id:                 " << itr -> idAdresat << endl;
                cout << "IdUzytkownik:       " << itr -> idUzytkownik << endl;
                cout << "Imie:               " << itr -> imieUzytkownik << endl;
                cout << "Nazwisko:           " << itr -> nazwiskoUzytkownik << endl;
                cout << "Numer Telefonu:     " << itr -> numerTelefonu << endl;
                cout << "Nr Email:           " << itr -> email << endl;
                cout << "Adres:              " << itr -> adres << endl;
                cout << "-------------------------" << endl;
            }
        }

        cout << "Podaj numer adresata ktorego chcesz usunac: ";
        cin >> numerKontaktuDoUsuniecia;

        if (cin.fail()) {
            cout << endl << "Wprowadzono niepoprawne dane. Powrot do menu glownego" << endl;
            cin.clear();
            cin.sync();
        } else {
            for (itr = adresaci.begin(); itr != adresaci.end(); itr++) {

                if (itr -> idAdresat == numerKontaktuDoUsuniecia) {
                    czyIstniejeAdresat = true;

                    cout << endl << "Potwierdz naciskajac klawisz 't': ";
                    cin >> znak;
                    if (znak == 't') {
                        itr = adresaci.erase(itr);
                        aktualizaujDanePoUsunieciuAdresata(numerKontaktuDoUsuniecia);
                        cout << endl << "Wskazany kontakt zostal USUNIETY" << endl << endl;

                        break;
                    } else {
                        cout << endl << endl << "Wybrany adresat NIE zostal usuniety" << endl << endl;
                        break;
                    }
                    cout << endl;
                    cout << "Jesli chcesz powrocic do menu glownego nacisnij dowolny klawisz" << endl;
                    wybor = getch();
                }
            }
            if (czyIstniejeAdresat == false) {
                cout << endl << "Nie ma takiego adresata w ksiazce adresowej" << endl << endl;
            }
        }
    }

    else {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    system("pause");
}

void edycjaKontaktu(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {

    system("cls");
    bool czyIstniejeAdresat = false;
    int wyborDanych;
    int numerKontaktuDoEdycji = 0;

    vector<Adresat>::iterator itr;

    if(!adresaci.empty()) {

        cout << "Spis kontaktow w ksiazce adesowej:" << endl;

        for(itr = adresaci.begin(); itr != adresaci.end(); itr++) {

            if(itr -> idUzytkownik == idZalogowanegoUzytkownika) {

                cout << "Id:                 " << itr -> idAdresat << endl;
                cout << "IdUzytkownik:       " << itr -> idUzytkownik << endl;
                cout << "Imie:               " << itr -> imieUzytkownik << endl;
                cout << "Nazwisko:           " << itr -> nazwiskoUzytkownik << endl;
                cout << "Numer Telefonu:     " << itr -> numerTelefonu << endl;
                cout << "Nr Email:           " << itr -> email << endl;
                cout << "Adres:              " << itr -> adres << endl;
                cout << "-------------------------" << endl;
            }
        }

        cout << "Podaj numer adresata ktorego chcesz edytowac: ";
        cin >> numerKontaktuDoEdycji;

        if(cin.fail()) {
            cout << endl << "Wprowadzono niepoprawne dane. Powrot do menu glownego" << endl << endl;
            cin.clear();
            cin.sync();
        } else {
            for(itr = adresaci.begin(); itr != adresaci.end(); itr++) {

                if(itr -> idAdresat == numerKontaktuDoEdycji) {
                    czyIstniejeAdresat = true;
                    system("cls");
                    cout << "-----Panel edycji kontaktu-----" << endl;

                    cout << endl;

                    cout << "Id:                 " << itr -> idAdresat << endl;
                    cout << "IdUzytkownik:       " << itr -> idUzytkownik << endl;
                    cout << "Imie:               " << itr -> imieUzytkownik << endl;
                    cout << "Nazwisko:           " << itr -> nazwiskoUzytkownik << endl;
                    cout << "Numer Telefonu:     " << itr -> numerTelefonu << endl;
                    cout << "Nr Email:           " << itr -> email << endl;
                    cout << "Adres:              " << itr -> adres << endl;
                    cout << "-------------------------" << endl;

                    cout << endl;
                    cout << "-----Wybierz dostepne opcje-----" << endl;
                    cout << "1. Zmiana imienia" << endl;
                    cout << "2. Zmiana nazwiska" << endl;
                    cout << "3. Zmiana numeru telefonu" << endl;
                    cout << "4. Zmiana adresu email" << endl;
                    cout << "5. Zmiana adresu" << endl;
                    cout << "6. Powrot" << endl;
                    cout << endl << "Wybierz 1-6: ";
                    cin >> wyborDanych;
                    cout << endl;

                    switch(wyborDanych) {
                    case 1:
                        cout << "Podaj nowe imie: ";
                        cin >> itr -> imieUzytkownik;
                        aktualizaujDaneEdytowanegoAdresata(*itr, numerKontaktuDoEdycji);
                        cout << "Zapisano pomyslnie zmiany";
                        break;
                    case 2:
                        cout << "Podaj nowe nazwisko: ";
                        cin >> itr -> nazwiskoUzytkownik;
                        aktualizaujDaneEdytowanegoAdresata(*itr, numerKontaktuDoEdycji);
                        cout << "Zapisano pomyslnie zmiany";
                        break;
                    case 3:
                        cout << "Podaj nowy numer telefonu: ";
                        cin.sync();
                        getline(cin, itr -> numerTelefonu);
                        aktualizaujDaneEdytowanegoAdresata(*itr, numerKontaktuDoEdycji);
                        cout << "Zapisano pomyslnie zmiany";
                        break;
                    case 4:
                        cout << "Podaj nowy adres email: ";
                        cin >> itr -> email;
                        aktualizaujDaneEdytowanegoAdresata(*itr, numerKontaktuDoEdycji);
                        cout << "Zapisano pomyslnie zmiany";
                        break;
                    case 5:
                        cout << "Podaj nowy adres: ";
                        cin.sync();
                        getline(cin, itr -> adres);
                        aktualizaujDaneEdytowanegoAdresata(*itr, numerKontaktuDoEdycji);
                        cout << "Zapisano pomyslnie zmiany";
                        break;
                    case 6:
                        break;
                    }
                    cout << endl;
                    if(czyIstniejeAdresat == false) {
                        cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
                    }
                }
            }
        }
    } else
        cout << "Ksiazka adresowa jest pusta." << endl << endl;

    system("pause");
}

void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {

    wczytajOsobyZPlikuUzytkownicy(uzytkownicy);
    string haslo = "";
    cout << "Podaj nowe haslo: ";
    cin >> haslo;

    for(unsigned int i = 0; i < uzytkownicy.size(); i++) {

        if(uzytkownicy[i].idUzytkownik == idZalogowanegoUzytkownika) {

            uzytkownicy[i].hasloUzytkownik = haslo;
            zapiszPlikUzytkownicy(uzytkownicy);

            cout << "Haslo zostalo zmienione" << endl;
            Sleep(2000);
        }
    }
}

void koniecProgramu() {

    cout << endl << "Koniec programu." << endl;
    exit(0);
}

int main() {

    vector<Uzytkownik> uzytkownicy;
    vector<Adresat> adresaci;
    int idZalogowanegoUzytkownika = 0;
    int wybor = 0;
    int iDOstatniegoAdresataWPliku = 0;
    Uzytkownik uZytkownik;

    if(uzytkownicy.empty() == true) {
        fstream plik;
        plik.open("Uzytkownicy.txt", ios::out | ios::app);
    }

    while(true) {

        if(idZalogowanegoUzytkownika == 0) {
            system("cls");
            cout << "1. Rejestraja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zamknij programu" << endl;
            cin >> wybor;

            switch(wybor) {
            case 1:
                rejestracja(uzytkownicy);
                break;
            case 2:
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                break;
            case 9:
                koniecProgramu();
                break;
            }
        }

        else {

            if(adresaci.empty() == true) {
                fstream plik;
                plik.open("Adresaci.txt", ios::out | ios::app);
            }
            iDOstatniegoAdresataWPliku = wczytajOsobyZPlikuAdresaci(adresaci, idZalogowanegoUzytkownika);

            system("cls");
            cout << "1. Dodaj nowy kontakt" << endl;
            cout << "2. Wyszukiwanie po imieniu" << endl;
            cout << "3. Wyszukiwanie po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edycja adresata" << endl;
            cout << "7. Zmiana hasla" << endl;
            cout << "8. Wylogowanie" << endl;
            cin >> wybor;

            switch(wybor) {

            case 1:
                idZalogowanegoUzytkownika = dodawanieKontaktu(adresaci, idZalogowanegoUzytkownika, iDOstatniegoAdresataWPliku);
                adresaci.clear();
                break;
            case 2:
                wyszukiwaniePoImieniu(adresaci, idZalogowanegoUzytkownika);
                adresaci.clear();
                break;
            case 3:
                wyszukiwaniePoNazwisku(adresaci, idZalogowanegoUzytkownika);
                adresaci.clear();
                break;
            case 4:
                wyswietlListeKontaktow(adresaci, idZalogowanegoUzytkownika);
                adresaci.clear();
                break;
            case 5:
                usunKontakt(adresaci, idZalogowanegoUzytkownika);
                adresaci.clear();
                break;
            case 6:
                edycjaKontaktu(adresaci, idZalogowanegoUzytkownika);
                adresaci.clear();
                break;
            case 7:
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                adresaci.clear();
                break;
            case 8:
                idZalogowanegoUzytkownika = 0;
                adresaci.clear();
                break;
            }
        }
    }
    return 0;
}
