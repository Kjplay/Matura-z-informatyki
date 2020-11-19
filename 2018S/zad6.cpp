#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
bool anagram(string a, string b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return (a == b);
}
int main() {
    ifstream dane;
    ofstream wynik;
    dane.open("slowa.txt");
    wynik.open("wyniki6.txt");
    if (dane.good() && wynik.good()) {
        string a, b;
        int last_a = 0, b_cont_a = 0, ana = 0;
        vector <string> pary;
        for (;;) {
            dane >> a >> b;
            if (!dane.fail()) {
                if (a[a.size() - 1] == 'A') last_a++;
                if (b[b.size() - 1] == 'A') last_a++;
                if (b.size() >= a.size()) {
                    if (b.find(a) != string::npos) b_cont_a++;
                }
                if (anagram(a, b)) {
                    ana++;
                    pary.push_back(a + " " + b);
                }
            } else {
                if (dane.eof()) {
                    wynik << "6.1" << endl;
                    wynik << "Liczba wyrazow z ostania litera 'A': " << last_a << endl;
                    wynik << "6.2" << endl;
                    wynik << "Liczba wierszy, gdzie b zawiera a: " << b_cont_a << endl;
                    wynik << "6.3" << endl;
                    wynik << "Liczba wierszy, gdzie a i b to anagramy: " << ana << endl;
                    wynik << "Pary anagramow:" << endl;
                    for (int i=0; i < pary.size();i++) {
                        wynik << pary[i] << endl;
                    }
                    break;
                }
                if (dane.bad()) {
                    cout << "blad krytyczny";
                    return 2;
                }
            }
        }
    } else {
        cout << "sprawdz czy plik slowa.txt istnieje" << endl << "blad w otwrcziu/utworzeniu pliku/ow!";
        return 1;
    }
    dane.close();
    wynik.close();
    return 0;
}
