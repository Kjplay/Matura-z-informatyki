#include <array>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
bool liczba_pierwsza(int n) {
    for (int i=2; i*i <= n; i++) if (n%i == 0) return false;
    return true;
}
int suma_cyfr (int n) {
    int s = 0;
    while (n > 0) {
        s += n % 10;
        n /= 10;
    }
    return s;
}
struct trojka {
    bool check = false;
    array <long int, 3> liczby;
    bool zad1() { return ((suma_cyfr(liczby[0]) + suma_cyfr(liczby[1])) == liczby[2]); }
    bool zad2() { return (liczba_pierwsza(liczby[0]) && liczba_pierwsza(liczby[1]) && (liczby[0]*liczby[1]) == liczby[2]); }
    bool zad3() {
        array <long int, 3> sorted = liczby;
        sort(sorted.begin(), sorted.end());
        return (((sorted[0]*sorted[0]) + (sorted[1]*sorted[1])) == (sorted[2]*sorted[2]));
    }
    bool ciag_trojkatny() {
        array <long int, 3> sorted = liczby;
        sort(sorted.begin(), sorted.end());
        return ((sorted[0] + sorted[1]) > sorted[2]);
    }
    void wypisz(ostream &o) { o << liczby[0] << " " << liczby[1] << " " << liczby[2] << "\n"; }
};
using para_trojek = array<trojka, 2>;
int main() {
    ifstream dane("trojki.txt");
    ofstream wynik("wyniki_trojki.txt");
    vector <trojka> w1, w2;
    vector <para_trojek> w3;
    int cd = 1, cd_max = 0, w4 = 0;
    int a, b, c;
    trojka poprzedni;
    while (dane >> a >> b >> c) {
        trojka t;
        t.check = true;
        t.liczby = {a, b, c};
        if (t.zad1()) w1.push_back(t); //1
        if (t.zad2()) w2.push_back(t); //2
        if (t.ciag_trojkatny()) w4++; //4_1
        if (poprzedni.check) { 
            //3
            if (t.zad3() && poprzedni.zad3()) {
                para_trojek par = {poprzedni, t};
                w3.push_back(par);
            }
            //4_2
            if (poprzedni.ciag_trojkatny() && t.ciag_trojkatny()) cd++;
            else {
                cd_max = cd > cd_max ? cd : cd_max;
                cd = 1;
            }
        }
        poprzedni = t;
    }
    cd_max = cd > cd_max ? cd : cd_max; //jezeli ciag konczy sie wraz z plikiem
    dane.close();
    wynik << "1\n";
    for (trojka &t : w1) t.wypisz(wynik);
    wynik << "\n2\n";
    for (trojka &t : w2) t.wypisz(wynik);
    wynik << "\n3\n";
    for (para_trojek &p : w3) {
        for (trojka &t : p) t.wypisz(wynik);
        wynik << "\n";
    }
    wynik << "4\n";
    wynik << "Wiersze trojkatne: " << w4 << "\n";
    wynik << "Najdluzsy ciag: " << cd_max << "\n";
    wynik.close();
    return 0;
}