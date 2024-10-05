#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>


using namespace std;

struct Osoba
{
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu ="", email ="", adres ="";
};

char wczytajZnak()
{
    string wejscie = "";
    char znak = {0};

    while (true)
    {
        getline(cin, wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}


string wczytajLinie()
{
    string wejscie ="";

    cin.sync();
    getline(cin, wejscie);
    return wejscie;
}

int wczytajLiczbeCalkowita()
{
    string wejscie;
    int liczba;

    while(true)
    {
        getline(cin, wejscie);
        stringstream myStream(wejscie);

        if (myStream >> liczba)
        {
            break;
        }
        cout << "To nie jest liczba. Wpisz ponownie." << endl;
    }
    return liczba;
}



int wczytajOsobyZPliku (vector <Osoba> &osoby)
{
    Osoba osoba;
    string linia = "", wyraz = "";
    int nrKreski = 0, ostatniNumerId = 0;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good() == false)
    {
        return 0;
    }
    while (getline(plik, linia))
    {

        for (int i = 0; i < linia.length(); i++)
        {

            if (linia[i] != '|')
            {
                wyraz += linia [i];
            }

            else
            {
                nrKreski ++;


                switch (nrKreski)
                {
                case 1:
                    osoba.id = stoi(wyraz);
                    wyraz = "";
                    break;
                case 2:
                    osoba.imie = wyraz;
                    wyraz = "";
                    break;
                case 3:
                    osoba.nazwisko = wyraz;
                    wyraz = "";
                    break;
                case 4:
                    osoba.numerTelefonu = wyraz;
                    wyraz = "";
                    break;
                case 5:
                    osoba.email= wyraz;
                    wyraz = "";
                    break;
                case 6:
                    osoba.adres = wyraz;
                    wyraz = "";
                    osoby.push_back(osoba);
                    nrKreski = 0;
                    break;
                }
            }
        }
    }
    plik.close();

    return ostatniNumerId = osoba.id;
}


void dodajOsobeDoPliku (Osoba osoba)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good() == true)
    {
        plik << osoba.id << "|";
        plik << osoba.imie << "|";
        plik << osoba.nazwisko << "|";
        plik << osoba.numerTelefonu << "|";
        plik << osoba.email << "|";
        plik << osoba.adres << "|" <<endl;
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    plik.close();
}

int dodajOsobe (vector <Osoba> &osoby, int numerKolejnegoId)
{
    Osoba osoba;

    osoba.id = numerKolejnegoId + 1;

    cout <<"Podaj imie: ";
    osoba.imie = wczytajLinie();

    cout <<"Podaj nazwisko: ";
    osoba.nazwisko = wczytajLinie();

    cout <<"Podaj numer telefonu: ";
    osoba.numerTelefonu = wczytajLinie();

    cout <<"Podaj email: ";
    osoba.email = wczytajLinie();

    cout <<"Podaj adres: ";
    osoba.adres = wczytajLinie();

    cout << endl;
    cout << "Osoba zostala dodana" << endl;

    numerKolejnegoId++;

    osoby.push_back(osoba);

    system("pause");

    dodajOsobeDoPliku(osoba);

    return numerKolejnegoId;
}


void wyszukajPoImieniu(vector <Osoba> &osoby)
{
    Osoba osoba;
    string poszukiwaneImie = "";
    int liczbaTakichSamychImion = 0;

    cout << "Podaj imie, ktore chcesz wyszukac" << endl << endl;

    poszukiwaneImie = wczytajLinie();

    cout << endl;

    if (osoby.size()== 0)
    {
        cout << "Plik nie zostal jeszcze stworzony" << endl << endl;
    }
    else
    {
        for (Osoba osoba : osoby)
        {
            if (osoba.imie == poszukiwaneImie)
            {
                cout << setw(25)<< left << "Id: "            << osoba.id<< endl;
                cout << setw(25)<< left <<"Imie: "           << osoba.imie<< endl;
                cout << setw(25)<< left <<"Nazwisko: "       << osoba.nazwisko << endl;
                cout << setw(25)<< left <<"Numer telefonu: " << osoba.numerTelefonu<< endl;
                cout << setw(25)<< left <<"Email:"           << osoba.email<< endl;
                cout << setw(25)<< left <<"Adres:"           << osoba.adres<< endl << endl;
                liczbaTakichSamychImion++;
            }
        }
        if (liczbaTakichSamychImion == 0)
        {
            cout << "Na liscie nie ma osoba o takim imieniu" << endl << endl;
        }

    }

    system("pause");
}

void wyszukajPoNazwisku(vector <Osoba> &osoby)
{

    int  liczbaTakichSamychNazwisk = 0;
    string poszukiwaneNazwisko = "";

    cout << "Podaj nazwisko, ktore chcesz wyszukac" << endl << endl;

    poszukiwaneNazwisko = wczytajLinie();

    cout << endl;

    if (osoby.size() == 0)
    {
        cout << "Plik nie zostal jeszcze stworzony" << endl << endl;
    }
    else
    {
        for (Osoba osoba : osoby)
        {
            if (osoba.nazwisko == poszukiwaneNazwisko)
            {
                cout << setw(25)<< left <<"Id: "             << osoba.id<< endl;
                cout << setw(25)<< left <<"Imie: "           << osoba.imie<< endl;
                cout << setw(25)<< left <<"Nazwisko: "       << osoba.nazwisko << endl;
                cout << setw(25)<< left <<"Numer telefonu: " << osoba.numerTelefonu<< endl;
                cout << setw(25)<< left <<"Email:"           << osoba.email<< endl;
                cout << setw(25)<< left <<"Adres:"           << osoba.adres<< endl << endl;
                liczbaTakichSamychNazwisk++;
            }
        }
        if (liczbaTakichSamychNazwisk == 0)
        {
            cout << "Na liscie nie ma osoba o takim nazwisku" << endl << endl;
        }
    }
    system("pause");
}


void wyswietlWszystkichAdresatow(vector <Osoba> &osoby)
{
    Osoba osoba;

    for (Osoba osoba : osoby)
    {
        cout << setw(25)<< left <<"Id: "              << osoba.id<< endl;
        cout << setw(25)<< left <<"Imie: "            << osoba.imie<< endl;
        cout << setw(25)<< left <<"Nazwisko: "        << osoba.nazwisko << endl;
        cout << setw(25)<< left <<"Numer telefonu: "  << osoba.numerTelefonu<< endl;
        cout << setw(25)<< left <<"Email:"            << osoba.email<< endl;
        cout << setw(25)<< left <<"Adres:"            << osoba.adres<< endl << endl;

    }

    if (osoby.size() == 0)
    {
        cout << "Plik nie zostal jeszcze stworzony" << endl << endl;
    }

    system("pause");
}

void nadpiszPlik (vector <Osoba> &osoby )
{
    Osoba osoba;

    fstream plik2;
    plik2.open("temp.txt", ios::out);

    if (plik2.good() == true)
    {
        for (Osoba osoba : osoby)
        {
            plik2 << osoba.id << "|";
            plik2 << osoba.imie << "|";
            plik2 << osoba.nazwisko << "|";
            plik2 << osoba.numerTelefonu << "|";
            plik2 << osoba.email << "|";
            plik2 << osoba.adres << "|"  << endl;
        }
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
    plik2.close();

    remove("KsiazkaAdresowa.txt");
    rename("temp.txt", "KsiazkaAdresowa.txt");
}


void usunAdresata (vector <Osoba> &osoby)
{
    Osoba osoba;
    char idDoUsuniecia, potwierdzenieWyboru;

    cout << "Podaj id osoby, ktora chcesz usunac" << endl;
    idDoUsuniecia = wczytajLiczbeCalkowita();

    cout << "Potwierdz usuniecie danego adresata, wciskajac klawisz 't' " << endl;
    potwierdzenieWyboru = wczytajZnak();

    if (potwierdzenieWyboru == 't')
    {
        for (vector <Osoba> :: iterator itr = osoby.begin(); itr!= osoby.end(); itr++)
        {
            if (itr -> id == idDoUsuniecia)
            {
                osoby.erase(itr);
                if (itr == osoby.end())
                {
                    break;
                }
            }
        }

    }
    else
    {
        cout << "Nieprawidlowy klawisz. Adresat nie zostal usuniety" << endl;
    }

    nadpiszPlik(osoby);
    system("pause");
}


void zmienDaneAdresata (vector <Osoba> &osoby)
{
    Osoba osoba;
    char wyborOpcji;
    char wybor;

    cout << "Wpisz id adresata, ktorego dane chcesz zmienic" << endl;
    wybor = wczytajLiczbeCalkowita();
    cout << endl;


    cout << ">>> OPCJE DO ZMIANY <<<" << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer telefonu" << endl;
    cout << "4. Email" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Powrot do menu" << endl << endl;

    cout << "Wybierz, ktora dana chcesz zmienic" << endl;
    wyborOpcji = wczytajZnak();

    for (vector <Osoba> :: iterator itr = osoby.begin(); itr!= osoby.end(); itr++)
    {
        if (itr -> id == wybor)
        {
            switch (wyborOpcji)
            {
            case '1':
                cout << "Podaj imie do zmiany" << endl;
                itr -> imie = wczytajLinie();
                cout << "Dane adresata zostaly zmienione" << endl;
                break;
            case '2':
                cout << "Podaj nazwisko do zmiany" << endl;
                itr -> nazwisko = wczytajLinie();
                cout << "Dane adresata zostaly zmienione" << endl;
                break;
            case '3':
                cout << "Podaj numer telefonu do zmiany" << endl;
                itr -> numerTelefonu = wczytajLinie();
                cout << "Dane adresata zostaly zmienione" << endl;
                break;
            case '4':
                cout << "Podaj email do zmiany" << endl;
                itr -> email = wczytajLinie();
                cout << "Dane adresata zostaly zmienione" << endl;
                break;
            case '5':
                cout << "Podaj adres do zmiany" << endl;
                itr -> adres = wczytajLinie();
                cout << "Dane adresata zostaly zmienione" << endl;
                break;
            case '6':
                break;

            }
        }
    }

    nadpiszPlik(osoby);
    system("pause");

}


int main()
{
    vector <Osoba> osoby;
    Osoba osoba;
    char wybor;
    int numerKolejnegoId = 0;

    numerKolejnegoId = wczytajOsobyZPliku(osoby);


    while(1)
    {

        system ("cls");
        cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl << endl << endl;


        cout << "Twoj wybor: ";
        wybor = wczytajZnak();
        cout << endl;

        switch (wybor)
        {

        case '1':
            numerKolejnegoId= dodajOsobe(osoby, numerKolejnegoId);
            break;

        case  '2':
            wyszukajPoImieniu(osoby);
            break;

        case '3':

            wyszukajPoNazwisku (osoby);
            break;

        case '4':

            wyswietlWszystkichAdresatow(osoby);
            break;

        case '5':

            usunAdresata (osoby);
            break;

        case '6':

            zmienDaneAdresata (osoby);
            break;

        case'9' :

                exit(0);
            break;

        }
    }

    return 0;
}
