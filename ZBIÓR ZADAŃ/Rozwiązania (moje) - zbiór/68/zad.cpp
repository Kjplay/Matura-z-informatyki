#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
/* Na 3 podpunkt sa 2 sposoby
1. Wywal wszystkie stringi przesortowane do vectora i posortuj caly vector - policz ile jest tego pierwszego
2. Zliczaj posortowane przy wczytywaniu do mapy, a potem znajdz największy - ja obralem ten sposob
*/
using namespace std;
void sortuj(string &s, string &z) {
    sort(s.begin(), s.end());
    sort(z.begin(), z.end());
}
bool jednolite_anagram(string s, string z) {
    char c = s[0];
    for (char t : s) if (t != c) return false;
    return (s == z);
}
bool anagramy(string s, string z) {
    if (s.length() != z.length()) return false;
    sortuj(s, z);
    return (s == z);
}
int main() {
    ifstream dane("dane_napisy.txt");
    ofstream wynik("wyniki_anagramy.txt");
    map<string, int> napisy;
    string a, b;
    int w1 = 0, w2 = 0;
    while (dane >> a >> b) {
        if (jednolite_anagram(a, b)) w1++;
        if (anagramy(a, b)) w2++;
        sortuj(a, b);
        napisy[a]++;
        napisy[b]++;
    }
    dane.close();
    int w3 = 0;
    for (pair <string, int> p : napisy) if (p.second > w3) w3 = p.second;
    wynik << "68.1\n" << w1 << "\n68.2\n" << w2 << "\n68.3\n" << w3;
    wynik.close();
    return 0;
}   