#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
array <array <char, 30>, 30> importdzialka(ifstream &plik) {
    array <array <char, 30>, 30> dzialka;
    for (int i=0; i < 30; i++) {
        string linia;
        plik >> linia;
        if (plik.fail()) {
            dzialka[0][0] = 'N'; //moze byc pusta linia na koncu pliku -> sprawdz czy dzialka istnieje
            break;
        } 
        for (int j=0; j < 30 ; j++) {
            dzialka[i][j] = linia[j];
        }
    }
    return dzialka;
}
map <char, int> policz(array <array <char, 30>, 30> dzialka) {
    map <char, int> mapa;
    for (int i=0; i < 30; i++) {
        for (int j=0; j < 30 ; j++) {
            mapa[dzialka[i][j]]++;
        }
    }
    return mapa;
}
int plac(array <array <char, 30>, 30> dzialka) {
    int x = 30;
    while(x > 0) {
        bool ok = true;
        for (int i=0; i < x; i++) {
            for (int j=0; j < x ; j++) {
                if (dzialka[i][j] == 'X') {
                    ok = false;
                    break;
                }
            }
            if (ok == false) break;
        }
        if (ok == true) break;
        x--; 
    }
    return x;
}
void obroc (array <array <char, 30>, 30> &dzialka) {
    reverse(dzialka.begin(), dzialka.end());
    for (array <char, 30> &row : dzialka) {
        reverse(row.begin(), row.end());
    }
}
void print(array <array <char, 30>, 30> dzialka) {
    for (array <char, 30> row : dzialka) {
        for (char x : row) cout << x;
        cout << "\n";
    }
}
int main() {
    ifstream dane("dzialki.txt");
    ofstream plik_wynik("wynik4.txt");
    vector <array <array <char, 30>, 30> > dzialki;
    //wczytaj dzialki
    for (;;) {
        string temp;
        array <array <char, 30>, 30> dzialka;
        dzialka = importdzialka(dane);
        if (dzialka[0][0] == 'N') break;
        else dzialki.push_back(dzialka);
        getline(dane, temp);
        if (temp != "") break; //pusta linia miedzy dzialkami 
    }
    //4.1 i 4.3
    int wynik1 = 0, wynik3plac = 0;
    vector <int> wynik3num;
    int x = 1;
    for (array <array <char, 30>, 30> dzialka : dzialki) {
        //4.1
        map <char, int> dane = policz(dzialka);
        if (dane['*']/((dane['.']+dane['*']+dane['X'])*1.0) >= 0.7) wynik1++; //*1.0 zeby nie było dzielenia calkowitego
        //4.3
        int plac_size = plac(dzialka);
        if (plac_size > wynik3plac) {
            wynik3plac = plac_size;
            wynik3num.clear();
            wynik3num.push_back(x);
        } else if (plac_size == wynik3plac) wynik3num.push_back(x);
        x++;
    }  
    //4.2
    int wynik21 = -1, wynik22 = -1;
    for (int i=0; i < dzialki.size(); i++) {
        for (int j=i+1; j < dzialki.size(); j++) {
            array <array <char, 30>, 30> temp = dzialki[j];
            obroc(temp);
            if (dzialki[i] == temp) {
                wynik21 = i+1;
                wynik22 = j+1;
                break;
            }
        }
        if (wynik21 != -1) break;
    }
    plik_wynik << "WYNIKI" << "\n";
    plik_wynik << "4.1\n" << wynik1 << "\n";
    plik_wynik << "4.2\n" << wynik21 << ", " << wynik22 << "\n";
    plik_wynik << "4.3\n" << "Rozmiar placu: " << wynik3plac << "\nNr dzialki/ek: ";
    for (int x : wynik3num) plik_wynik << x << " ";
    plik_wynik << "\n";
}