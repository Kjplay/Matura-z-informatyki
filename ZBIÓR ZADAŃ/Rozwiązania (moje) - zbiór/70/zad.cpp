#include <cmath>
#include <fstream>
#include <iostream>
#include <tuple>
using namespace std;
using point = tuple<double, double>;
const double TOP = 19+(61.0/125.0);
const double BOTTOM = -32-(2.0/3.0);
const double LEFT = 2;
const double RIGHT = 10;
double f(double x) {
    return (pow(x, 4)/500)-(pow(x, 2)/200)-0.012;
}
double g(double x) {
    return (-1.0*(pow(x, 3)/30))+(x/20)+(1.0/6);
}
double pole(double blad = 0.001) {
    int steps = 10;
    double pf, pg;
    double poleg = 0, poled = 0;
    double x, r;
    //f
    do {
        poleg = 0; poled = 0;
        x = LEFT;
        r = (RIGHT-LEFT)/steps;
        for (int i=0; i < steps; i++) {
            poled += f(x);
            x += r;
            poleg += f(x);
        }
        poleg *= r;
        poled *= r;
        steps *=2;
    } while (poleg-poled>blad/2); //sprawdzamy czy miesci sie w bledzie
    pf = (poleg+poled)/2;
    //reset
    steps = 10;
    //g
    do {
        poleg = 0; poled = 0;
        x = LEFT;
        double r = (RIGHT-LEFT)/steps;
        for (int i=0; i < steps; i++) {
            poled -= g(x); //odejmujemy g bo ujemne
            x += r;
            poleg -= g(x);
        }
        poleg *= r;
        poled *= r;
        steps *=2;
    } while (poleg-poled>blad/2); //sprawdzamy czy miesci sie w bledzie
    pg = (poleg+poled)/2;
    return pf+pg;
}
double odleglosc (point a, point b) {
    auto [xa, ya] = a;
    auto [xb, yb] = b;
    return sqrt(pow(xb-xa, 2)+pow(yb-ya, 2));
}
double obwod(int steps = 1000) {
    double sum = 0;
    sum += TOP-BOTTOM;
    sum += (RIGHT-LEFT)*2;
    //f
    double x = LEFT;
    double r = (RIGHT-LEFT)/steps*1.0;
    point before{x, f(x)};
    for (int i=1; i < steps+1; i++) {
        x += r;
        point now{x, f(x)};
        sum += odleglosc(before, now);
        before = now;
    }
    //g
    x = LEFT;
    before = {x, g(x)};
    for (int i=1; i < steps+1; i++) {
        x += r;
        point now{x, g(x)};
        sum += odleglosc(before, now);
        before = now;
    }
    return sum;
}
double pasy(double szer = 0.25) {
    double sum = 0;
    for (double x = RIGHT-szer; x >= LEFT; x-=szer) sum += floor(f(x)-g(x));
    return sum;
}
int main() {
    double w1 = pole();
    int w2 = ceil(obwod());
    double w3 = pasy();
    ofstream wynik("zadanie_zaslona.txt");
    wynik << "70.1\nIlosc pozostałego materiału: " << w1 << "\n";
    wynik << "70.2\nIlosc tasmy do zakupienia: " << w2 << "m\n";
    wynik << "70.3\nLaczna dlugosc pasow: " << w3;
    wynik.close();
    return EXIT_SUCCESS;
}