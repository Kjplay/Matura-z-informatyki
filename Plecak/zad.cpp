#include <vector>
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;
using przedmiot = array<int, 2>;

bool por_wartosc(przedmiot a, przedmiot b) {
    return a[0] > b[0];
}
bool por_waga(przedmiot a, przedmiot b) {
    return a[1] < b[1];
}
bool por_iloraz(przedmiot a, przedmiot b) {
    return a[0]*1.0/a[1] > b[0]*1.0/b[1];
}
int pleacak(vector <przedmiot> p, int miejsce, string typ = "wartosc", bool jeden=false) {
    int i = 0, suma = 0;
    if (typ == "wartosc") sort(p.begin(), p.end(), por_wartosc);
    else if (typ == "waga") sort(p.begin(), p.end(), por_waga);
    else if (typ == "iloraz") sort(p.begin(), p.end(), por_iloraz);
    else cout << "Nie rozpoznano kryterium\n";
    while (miejsce > 0) {
        if (p[i][1] <= miejsce) {
            miejsce -= p[i][1];
            suma += p[i][0];
            if (jeden) {
                if (++i >= p.size()) break;
            }
        } else if (i++ >= p.size()) break;
    }
    return suma;
}

int main() {
    vector <przedmiot> v = { {6, 6}, {4, 2}, {5, 3}, {7, 2}, {10, 3}, {2, 1} };
    cout << "Wartosc: " << pleacak(v, 23, "wartosc") << "\n";
    cout << "Waga: " << pleacak(v, 23, "waga") << "\n";
    cout << "Iloraz: " << pleacak(v, 23, "iloraz") << "\n";
    cout << "Wartosc_jeden: " << pleacak(v, 23, "wartosc", true) << "\n";
    cout << "Waga_jeden: " << pleacak(v, 23, "waga", true) << "\n";
    cout << "Iloraz_jeden: " << pleacak(v, 23, "iloraz", true);
    return EXIT_SUCCESS;
}