#include <iostream>
#include <vector>
using namespace std;
int NWD(int a, int b) {
    int c;
    while (b != 0) {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}
int main () {
    cout << "Podaj ilosc liczb: ";
    int n;
    cin >> n;
    vector <int> liczby;
    for (int i=0;i<n;i++) {
        int y;
        cout << "Podaj ilczbê liczbe " << i+1 << ": ";
        cin >> y;
        liczby.push_back(y);
    }
    n = liczby.size();
    int x = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j=i+1; j<n; j++) {
            cout << "Indeksy pary: " << i << " " << j << " NWD: " << NWD(liczby[i], liczby[j]) << endl;
            if (NWD(liczby[i], liczby[j]) == 1) x++;
        }
    }
    cout << "Wynik: " << x;
    return 0;
}
