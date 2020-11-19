#include <map>
#include <array>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <cmath>
using namespace std;

const int ilosc = 5;

using wspolczynniki = map<int, array<double, 4>>;

wspolczynniki wspl_data; //global

void wczytaj(string nazwa) {
    ifstream dane(nazwa);
    for (int i=1; i<=ilosc;i++) {
        array<double, 4> a;
        dane >> a[3] >> a[2] >> a[1] >> a[0]; //odwrotnie, do schematu hornera
        ::wspl_data[i] = a; //edit global
    }
    dane.close();
}
double horner(double x, array<double, 4> wspl) {
    double a = wspl[0];
    for (int i=1;i < 4 ;i++) {
        a = (a*x) + wspl[i];
    }
    return a;
}
double f(double x) {
    if (x < 1.0) return horner(x, ::wspl_data[1]);
    else if (x < 2.0) return horner(x, ::wspl_data[2]);
    else if (x < 3.0) return horner(x, ::wspl_data[3]);
    else if (x < 4.0) return horner(x, ::wspl_data[4]);
    else return horner(x, ::wspl_data[5]);
}
tuple<double, double> maxi(double dokladnosc = 0.00001) {
    bool c = true;
    double out, x;
    for (double i = 0; i < 5.0; i += dokladnosc) {
        if (f(i) > out || c) {
            out = f(i);
            x = i;
            c = false;
        }
    }
    return {x, out};
}
double miejsce_zerowe(double from, double to) {
    double fleft = f(from);
    while (to-from > 1e-8) {
        double m = (to + from)/2.0;
        double fmiddle = f(m);
        if (fmiddle * fleft < 0.0) { //miejsce zerowe jest na lewo od middle
            to = m;
        } else {
            from = m;
            fleft = fmiddle;
        }
    }
    return (from+to)/2.0;
}
int main() {
    wczytaj("funkcja.txt");
    double w1 = round(f(1.5)*1e5)/1e5;
    auto [w2x, w2y] = maxi();
    vector<double> w3;
    for (double x = 0.0; x <= 4.0; x += 1.0) {
        if (f(x) * f(x+1.0) < 0.0) w3.push_back(round(miejsce_zerowe(x, x+1.0)*1e5)/1e5);
    }
    ofstream wynik("wyniki_funkcja.txt");
    wynik << "71.1\nf(1.5) = " << w1 << "\n";
    wynik << "71.2\nx = " << round(w2x*1e3)/1e3 << "\nf(x) = " << round(w2y*1e5)/1e5 << "\n71.3\n";
    for (double i : w3) wynik << "Miejsce zerowe: " << i << "\n";
    wynik.close();
    return EXIT_SUCCESS;
}