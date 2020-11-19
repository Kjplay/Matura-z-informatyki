#include <fstream>
#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#define all(x) begin(x), end(x)
using namespace std;

struct punkt {
    int x;
    int y;
};

struct dokladny_punkt {
    double x;
    double y;
};

using trojkat = array<punkt, 3>;
using czworokat = array<punkt, 4>;
int cwiartka (punkt p) {
    if (p.x > 0  && p.y > 0) return 1;
    else if (p.x < 0  && p.y > 0) return 2;
    else if (p.x < 0  && p.y < 0) return 3;
    else return 4;
}

int cwiartka (trojkat t) {
    int c = cwiartka(t[0]);
    if (c == cwiartka(t[1]) && c == cwiartka(t[2])) return c;
    else return 0;
}

bool na_prostej(trojkat t) {
    double a = (t[0].y - t[1].y)*1.0/(t[0].x - t[1].x)*1.0;
    double b = t[0].y*1.0-(a*t[0].x);
    if (t[2].y == a*t[2].x*1.0 + b) return true;
    else return false;
}

double odleglosc(punkt a, punkt b) {
    return sqrt(pow(b.x - a.x, 2)+pow(b.y - a.y, 2));
}

array<double, 3> boki (trojkat t) {
    return { odleglosc(t[0], t[1]), odleglosc(t[1], t[2]), odleglosc(t[0], t[2]) };
}

bool czy_trojkat(array<double, 3> b) {
    sort(all(b));
    return b[0] + b[1] > b[2];
}

bool czy_trojkat(trojkat t) {
    array <double, 3> b = boki(t);
    return czy_trojkat(b);
}
double obwod(array<double, 3> b) {
    return b[0]+b[1]+b[2];
}
bool czy_prostokatny(array<double, 3> b) {
    sort(all(b));
    return pow(b[0], 2)+pow(b[1], 2) == pow(b[2], 2);
}

bool czy_prostokatny(trojkat t) {
    array <double, 3> b = boki(t);
    return czy_prostokatny(b);
}

void print(czworokat c, ostream &o) {
    o << "(" << c[0].x << ", " << c[0].y << ") ";
    o << "(" << c[1].x << ", " << c[1].y << ") ";
    o << "(" << c[2].x << ", " << c[2].y << ") ";
    o << "(" << c[3].x << ", " << c[3].y << ")\n";
}

array<double, 2> rownoleglobok(trojkat t) {
    array <double, 3> b = boki(t);
    int max_index = distance(b.begin(), max_element(all(b))); //0 -> 0,1; 1 -> 1,2; 2-> 0,2
    dokladny_punkt m;
    if (max_index == 0) {
        m.x = (t[0].x+t[1].x)/2.0;
        m.y = (t[0].y+t[1].y)/2.0;
        return {2*m.x-t[2].x, 2*m.y-t[2].y};
    } else if (max_index == 1) {
        m.x = (t[1].x+t[2].x)/2.0;
        m.y = (t[1].y+t[2].y)/2.0;
        return {2*m.x-t[0].x, 2*m.y-t[0].y};
    } else {
        m.x = (t[0].x+t[2].x)/2.0;
        m.y = (t[0].y+t[2].y)/2.0;
        return {2*m.x-t[1].x, 2*m.y-t[1].y};
    }
}
int main() {
    ifstream dane1("wspolrzedne.txt");
    punkt a, b, c;
    trojkat w3t;
    vector<czworokat> w5;
    int w1 = 0, w2 = 0, w3m = 0, w4 = 0;
    int obw;
    while(dane1 >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y) {
        trojkat t = {a, b, c};
        if (cwiartka(t) == 1) w1++;
        if (na_prostej(t)) w2++;
    }
    dane1.close();
    ifstream dane2("wspolrzedneTR.txt");
    while(dane2 >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y) {
        trojkat t = {a, b, c};
        array<double, 3> b = boki(t);
        if (obwod(b) > w3m) {
            w3m = obwod(b);
            w3t = t;
        }
        if (czy_prostokatny(t)) w4++;
        array<double, 2> d = rownoleglobok(t);
        if (d[0] == d[1]) {
            czworokat c;
            punkt p;
            p.x = d[0];
            p.y = d[1];
            c[0] = t[0];
            c[1] = t[1];
            c[2] = t[2];
            c[3] = p;
            w5.push_back(c);
        }
    }
    dane2.close();
    ofstream wynik("wyniki.txt");
    wynik << "81.1\nLiczba wierszy: " << w1 << "\n";
    wynik << "81.2\nLiczba wierszy: " << w2 << "\n";
    wynik << "81.3\nNajwiekszy obwod: " << round(w3m*100)/100 << "\nWspolrzedne: (" << w3t[0].x << ", " << w3t[0].y << ") (" << w3t[1].x << ", " << w3t[1].y << ") (" << w3t[2].x << ", " << w3t[2].y << ")\n";
    wynik << "81.4\nTrojkaty prostokatne: " << w4 << "\n";
    wynik << "81.5 Wspolrzedne:\n";
    for (auto c : w5) print(c, wynik);
    return EXIT_SUCCESS;
}
