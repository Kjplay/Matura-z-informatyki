#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>
using namespace std;
using key = tuple<int, int>;

char szyfruj_litere (char c, key k) {
    int t = c - 'a';
    t = t*get<0>(k) + get<1>(k);
    t %= 26;
    c = t+ 'a';
    return c;
}
string szyfruj (string s, key k) {
    for (int i=0; i < s.length(); i++) s[i] = szyfruj_litere(s[i], k);
    return s;
}
bool D (string s) {
    return (s[0] == 'd' && s[s.length()-1] == 'd');
}
int main() {
    ifstream dane("tekst.txt");
    ofstream wynik("wyniki.txt");
    string s;
    vector <string> w1, w2;
    while (dane >> s) {
        if (D(s)) w1.push_back(s);
        if (s.length() >= 10) w2.push_back(szyfruj(s, {5, 2}));
    }
    dane.close();
    ifstream dane2("probka.txt");
    string a, b;
    int x = 0;
    wynik << "75.1\n";
    for (string s : w1) wynik << s << "\n";
    wynik << "75.2\n";
    for (string s : w2) wynik << s << "\n";
    wynik << "75.3\n";
    while (dane2 >> a >> b) {
        x++;
        key szy, des;
        bool c1 = false, c2 = false;
        for (int i=0; i <= 25; i++) {
            for (int j=0; j <= 25; j++) {
                if (szyfruj(a, {i, j}) == b) {
                    szy = {i, j};
                    c1 = true;
                    }
                if (szyfruj(b, {i, j}) == a) {
                    des = {i, j};
                    c2 = true;
                    }
                if (c1 && c2) break;
            }
            if (c1 && c2) break;
        }
        wynik << x << ". Szyfrujacy: (" << get<0>(szy) << ", " << get<1>(szy) << ")\n";
        wynik << x << ". Deszyfrujacy: (" << get<0>(des) << ", " << get<1>(des) << ")\n";
    }
    dane2.close();
    wynik.close();
    return EXIT_SUCCESS;
}