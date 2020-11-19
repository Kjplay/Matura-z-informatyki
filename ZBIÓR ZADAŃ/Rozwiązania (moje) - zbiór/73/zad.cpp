#include <fstream>
#include <map>
#include <cmath>
using namespace std;
const string vowls = "AEIOUY";
const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
bool zad1(string s) {
    for (int i=1; i < s.length(); i++) if (s[i-1] == s[i]) return true;
    return false;
}
bool is_consonant(char c) {
    for (char s : vowls) if (c == s) return false;
    return true;
}
int zad3(string s) {
    int l = 0, maxi = 0;
    for (char c : s) {
        if (is_consonant(c)) l++;
        else l=0;
        maxi = l > maxi ? l : maxi;
    }
    return maxi;
}
int main() {
    ifstream dane("tekst.txt");
    map <char, int> w2;
    for (char c : alphabet) w2[c] = 0; //define every letter in case of missing ones
    int w1 = 0, w2l = 0, w3m = 0, w3l = 0;
    string w3p = "";
    string s;
    while (dane >> s) {
        if(zad1(s)) w1++;
        for (char c : s) {
            w2[c]++;
            w2l++;
        }
        int temp = zad3(s);
        if (temp > w3m) {
            w3m = temp;
            w3p = s;
            w3l = 1;
        } else if (temp == w3m) w3l++;
    }
    dane.close();
    ofstream wynik("wyniki.txt");
    wynik << "73.1\nIlosc slow z dowma takimi samymi literami kolo siebie: " << w1 << "\n";
    wynik << "73.2\n";
    for (pair <char, int> p : w2) {
        double percentage = (p.second*1.0/w2l*1.0)*1e2;
        wynik << p.first << ": " << p.second << " (" << round(percentage*1e2)/1e2 << "%)\n"; //Zaokraglanie daje +- 0.01% inny wynik niz setprecision w iomanip
    }
    wynik << "73.3\nNajdluzsze podslowo: " << w3m << "\nLiczba slow z podslowe o tej dlugosci: " << w3l << "\nPierwsze slowo z podslowem o tej dlugosci: " << w3p << "\n";
    wynik << "NOTKA:\nJa zaokraglam do 2 miejsc po przecinku co może dac nieco inne wyniki (+- 0.01%) niż setprecision zastosowane w proponowanym roziwazaniu.\n\nTekst jest chyba z Wladcy Pierscieni :)";
    wynik.close();
    return EXIT_SUCCESS;
}