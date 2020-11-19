#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <vector>
#include <array>
using namespace std;
const int ILOSC = 2000;

struct okrag {
    double x;
    double y;
    double r;
};

int cwiartka(okrag o) {
    if (abs(o.x)-o.r > 0 && abs(o.y)-o.r > 0) {
        if (o.x > 0 && o.y > 0) return 1;
        else if (o.x < 0 && o.y > 0) return 2;
        else if (o.x < 0 && o.y < 0) return 3;
        else return 4;
    } else return 0;
}

bool lustrzane(okrag a, okrag b) {
    return ( a.r == b.r && ( (a.x == b.x && a.y == b.y*-1.0) || ((a.y == b.y && a.x == b.x*-1.0)) ) );
}

bool prostopadle(okrag a, okrag b) {
    return ( a.r == b.r && ( (a.y == b.x*-1.0 && a.x == b.y) || (a.x == b.y*-1.0 && b.x == a.y) ) );
}
bool punkt_wspolny(okrag a, okrag b) {
    double odleglosc = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    return (odleglosc >= abs(a.r - b.r) && odleglosc <= (a.r + b.r));
}

int main() {
    ifstream dane("okregi.txt");
    map <int, int> w1;
    int w2 = 0, w3 = 0, w4m = 0;
    vector <int> w4c;
    array <okrag, ILOSC> okregi;
    for (int i=0; i < ILOSC; i++) {
        okrag o;
        dane >> o.x >> o.y >> o.r;
        w1[cwiartka(o)]++;
        okregi[i] = o;
    }
    dane.close();
    for (int i=0; i < ILOSC; i++) {
        for (int j=i+1; j < ILOSC; j++) {
            if (lustrzane(okregi[i], okregi[j])) w2++;
            if (prostopadle(okregi[i], okregi[j])) w3++;
        }
    }
    int dlugosc = 1;
    for (int i=1; i < 1000; i++) {
        if (punkt_wspolny(okregi[i-1], okregi[i])) dlugosc++;
        else {
            if (dlugosc > w4m) w4m = dlugosc;
            w4c.push_back(dlugosc);
            dlugosc = 1;
        }
    }
    if (dlugosc > w4m) w4m = dlugosc;
    w4c.push_back(dlugosc);
    ofstream wynik("wyniki_okregi.txt");
    wynik << "79.1\nI cwiartka: " << w1[1] << "\nII ciwartka: " << w1[2] << "\nIII cwiartka: " << w1[3] << "\nIV cwiartka: " << w1[4] << "\npozostale: " << w1[0] << "\n";
    wynik << "79.2\nPary lustrzane: " << w2 << "\n";
    wynik << "79.3\nPary prostopadle: " << w3 << "\n";
    wynik << "79.4\n";
    for (int i : w4c) wynik << "Kolejny ciag: " << i << "\n";
    wynik << "Najdluzszy ciag: " << w4m;
    wynik.close();
    return EXIT_SUCCESS;
}