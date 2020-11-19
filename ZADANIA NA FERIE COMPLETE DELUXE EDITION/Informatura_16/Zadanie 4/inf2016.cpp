#include <fstream>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
bool anagram(string a, string b) {
    if (a.length() == b.length()) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        if (a == b) return true;
        else return false;
    } else {
        return false;
    }
}
int ile_substr(string str, string sub) {
    int ile = 0;
    size_t pos = str.find(sub, 0);
    while(pos != string::npos) {
        ile++;
        pos = str.find(sub,pos+1);
    }
    return ile;
}
int main() {
    ifstream dane;
    ofstream wynik;
    dane.open("hasla.txt");
    wynik.open("wyniki4.txt");
    if (dane.good() && wynik.good()) {
        int anagramy = 0;
        string a, b;
        string tr[6] = {"ABC", "ACB", "BAC", "BCA", "CAB", "CBA"};
        map <string, int> trojki;
        map <char, long int> litery;
        vector <string> hasla3;
        string alfabet = "ABCDEFGHIJKLMNOQPRSTUVWXYZ";
        for (;;) {
            dane >> a >> b;
            if (!dane.fail()) {
                if (anagram(a, b)) anagramy++;
                for (int i=0; i < 6; i++) {
                    int ile3a = 0;
                    ile3a = ile_substr(a, tr[i]);
                    if (ile3a > 1 && count(hasla3.begin(), hasla3.end(), a) == 0) hasla3.push_back(a);
                    trojki[tr[i]] += ile3a;
                    int ile3b = 0;
                    ile3b = ile_substr(b, tr[i]);
                    if (ile3b > 1 && count(hasla3.begin(), hasla3.end(), b) == 0) hasla3.push_back(b);
                    trojki[tr[i]] += ile3b;
                }
                for (int i=0;i < a.length(); i++) {
                    litery[a[i]]++;
                }
                for (int i=0;i < b.length(); i++) {
                    litery[b[i]]++;
                }
            } else {
                if (dane.eof()) {
                    char max_litera = '-';
                    char min_litera = '-';
                    int maxl = -1, minl = -1;
                    for (int i=0;i < alfabet.length(); i++) {
                        if (litery[alfabet[i]] > maxl || maxl == -1) {
                            max_litera = alfabet[i];
                            maxl = litery[alfabet[i]];
                        } else if (litery[alfabet[i]] == maxl) {
                            max_litera = '-';
                        }
                        if (litery[alfabet[i]] < minl || minl == -1) {
                            min_litera = alfabet[i];
                            minl = litery[alfabet[i]];
                        } else if (litery[alfabet[i]] == minl) {
                            min_litera = '-';
                        }
                    }
                    wynik << "4.1" << endl;
                    wynik << "Liczba lini anagramow: " << anagramy << endl;
                    wynik << "4.2"  << endl;
                    wynik << "Hasla z trojkami: " << endl;
                    for (int i=0; i < hasla3.size(); i++) {
                        wynik << hasla3[i] << endl;
                    }
                    wynik << "Trojki w pliku: " << endl;
                    for (int i=0; i < 6; i++) {
                        wynik << tr[i] << ": " << trojki[tr[i]] << endl;
                    }
                    wynik << "4.3" << endl;
                    if (max_litera == '-') {
                        wynik << "Brak litery wystepujacej naczesciej" << endl;
                    } else {
                        wynik << "Litera wystepujaca najczesciej: " << max_litera << endl;
                    }
                    if (min_litera == '-') {
                        wynik << "Brak litery wystepujacej najrzadziej" << endl;
                    } else {
                        wynik << "Litera wystepujaca najrzadziej: " << min_litera << endl;
                    }
                    break;
                } else if (dane.bad()) {
                    return 1;
                }
            }
        }
    }
    dane.close();
    wynik.close();
    return 0;
}
