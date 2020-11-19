#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <array>
using namespace std;
int NWD(int a, int b) {
    int t;
    while (b != 0){
        t = b;
        b = a%b;
        a = t;
    }
    return a;
}
int punkty_na_krawedzi(vector < array<int, 2> > a) {
    long int nwd_sum = 0;
    int x[2];
    int y[2];
    for (int i = 0; i < a.size(); i++) {
        x[0] = a[i][0];
        y[0] = a[i][1];
        for (int j = i+1;j < a.size(); j++) {
            x[1] = a[j][0];
            y[1] = a[j][1];
            nwd_sum += NWD(abs(x[0] - x[1]), abs(y[0] - y[1]));
        }
    }
    return nwd_sum;
}
double pole_wielokata(vector < array<int, 2> > a) {
    double pole_sum;
    vector < int > x;
    vector < int > y;
    for (int i = 0; i < a.size(); i++) {
        x.push_back(a[i][0]);
        y.push_back(a[i][1]);
    }
    // find min, max  -> x, y
    int min_x, min_y, max_x, max_y;
    min_x = x[distance(x.begin(), min_element(x.begin(), x.end()))];
    min_y = y[distance(y.begin(), min_element(y.begin(), y.end()))];
    max_x = x[distance(x.begin(), max_element(x.begin(), x.end()))];
    max_y = y[distance(y.begin(), max_element(y.begin(), y.end()))];
    pole_sum = (abs(max_x - min_x)*abs(max_y - min_y)); // rectangle
    for (int i = 1; i < a.size(); i++) {
        int point[2];
        point[0] = max(a[i-1][0], a[i][0]);
        point[1] = max(a[i-1][1], a[i][1]);
        pole_sum -= ((abs(a[i-1][0] - point[0])+abs(a[i][0] - point[0]))*(abs(a[i-1][1] - point[1])+abs(a[i][1] - point[1])))/2;
    }
    int point[2];
    point[0] = max(a[0][0], a[a.size()-1][0]);
    point[1] = max(a[0][1], a[a.size()-1][1]);
    pole_sum -= ((abs(a[0][0] - point[0])+abs(a[a.size()-1][0] - point[0]))*(abs(a[0][1] - point[1])+abs(a[a.size()-1][1] - point[1])))/2;
    return pole_sum;
}
int main() {
    ifstream dane;
    ofstream wynik;
    dane.open("wielokaty.txt");
    wynik.open("wynik4.txt");
    if (dane.good() && wynik.good()) {
        bool firstrun = true;
        int typ, cz_kat = 0, krat_max_1 = 0, krat_max_2 = 0, kraw_max_1, kraw_max_2;
        double max_pole_t, min_pole_t, r = 0, tr;
        long double sum_4 = 0;
        map < int, int > licznik;
        for (;;) {
            dane >> typ;
            if (!dane.fail()) {
                licznik[typ]++;
                int x, y;
                vector < array<int, 2> > wielokat;
                for (int i = 0 ; i < typ ; i++) {
                    dane >> x >> y;
                    tr = pow(pow(x,2)+pow(y, 2), 1.0/2.0);
                    if (tr > r) r = tr;
                    array <int, 2> point;
                    point[0] = x;
                    point[1] = y;
                    wielokat.push_back(point);
                }
                int kraw = punkty_na_krawedzi(wielokat);
                if (kraw > krat_max_1) {
                    krat_max_1 = kraw;
                    kraw_max_1 = typ;
                } else if (kraw > krat_max_2) {
                    krat_max_2 = kraw;
                    kraw_max_2 = typ;
                }
                double pole;
                pole = pole_wielokata(wielokat);
                if (typ == 3) { //triangle
                    if (firstrun) {
                        firstrun = false;
                        min_pole_t = pole;
                        max_pole_t = pole;
                    }
                    if (pole > max_pole_t) max_pole_t = pole;
                    else if (pole < min_pole_t) min_pole_t = pole;
                } else if (typ == 4) {
                    sum_4 += pole;
                    cz_kat++;
                }
            } else {
                if (dane.eof()) {
                    long double sr_pole_4 = floor((sum_4/cz_kat)*100)/100;
                    wynik << "4.1" << endl;
                    wynik << "Trojkaty: " << licznik[3] << " ;Pieciokaty: " << licznik[5] << endl;;
                    wynik << "4.2" << endl;
                    wynik << "Max pole trojkata: " << max_pole_t << endl;
                    wynik << "Min pole trojkata: " << min_pole_t << endl;
                    wynik << "4.3" << endl;
                    wynik << "Promien najmniejszego kola: " << r <<  endl;
                    wynik << "4.4" << endl;
                    wynik << "1. Punkty na krawedzi: " << krat_max_1 << " ;Krawedzie: " << kraw_max_1 << endl;
                    wynik << "2. Punkty na krawedzi: " << krat_max_2 << " ;Krawedzie: " << kraw_max_2 << endl;
                    wynik << "4.5" << endl;
                    wynik << "Srednie pole czworokata: " << sr_pole_4 << endl;
                    break;
                }
                if (dane.bad()) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
