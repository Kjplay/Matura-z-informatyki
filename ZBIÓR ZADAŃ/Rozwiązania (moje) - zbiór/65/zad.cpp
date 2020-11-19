#include <iostream>
#include <array>
#include <fstream>
#include <vector>
using namespace std;
const int podstawa = 573300; //2*2*3*3*5*5*7*7*13
int NWD(int a, int b) {
    while (b > 0) {
        int t = a;
        a = b;
        b = t % b;
    }
    return a;
}
struct ulamek {
    int licznik;
    int mianownik;
    float wartosc() {
        return (licznik*1.0)/(mianownik*1.0);
    }
    array<int,2> skrocony() {
        int a = licznik, b = mianownik;
        while(NWD(a, b) > 1) {
            int t = NWD(a, b);
            a /= t;
            b /= t;
        }
        return array<int, 2>{a, b};
    }
};
int main() {
    ifstream dane("dane_ulamki.txt");
    ofstream wynik("wynik_ulamki.txt");
    int a, b, wynik2 = 0, wynik3 = 0, wynik4 = 0;
    float minimum = -1;
    ulamek mini;
    while (dane >> a >> b) {
        ulamek u;
        u.licznik = a;
        u.mianownik = b;
        //1
        float w = u.wartosc();
        if (w < minimum || minimum == -1) {
            minimum = w;
            mini = u;
        } else if (w == minimum) {
            mini = mini.mianownik < u.mianownik ? mini : u;
        }
        //2
        array <int,2> ws{a, b};
        array <int, 2> sk = u.skrocony();
        if (ws == sk) wynik2++;
        //3
        wynik3 += sk[0];
        //4
        int mnoznik = podstawa/u.mianownik;
        wynik4 += (u.licznik*mnoznik);
    }
    wynik << "1\n" << mini.licznik << "/" << mini.mianownik << "\n";
    wynik << "2\n" << wynik2 << "\n";
    wynik << "3\n" << wynik3 << "\n";
    wynik << "4\n" << wynik4 << "\n";
    dane.close();
    wynik.close();
    return 0;
}