#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <iostream>
using namespace std;
const string alphabet = "ABCDEFGHIJKLMNOPQRSTUWVXYZ";
string vinegere(string s, string key) {
    int pop = 0;
    for (int i=0; i < s.length(); i++) {
        if (alphabet.find(s[i]) != string::npos) {
            int x = s[i] - 'A';
            int y = key[(i-pop) % key.size()] - 'A';
            x = (x+y) % 26;
            s[i] = x + 'A';
        } else pop++;
    }
    return s;
}
string un_vinegere(string s, string key) {
    int pop = 0;
    for (int i=0; i < s.length(); i++) {
        if (alphabet.find(s[i]) != string::npos) {
            int x = s[i] - 'A';
            int y = key[(i-pop) % key.size()] - 'A';
            x -= y;
            if (x < 0) x += 26;
            s[i] = x + 'A';
        } else pop++;
    }
    return s;
}
map <char, int> wystapienia(string s) {
    map <char, int> wys;
    for (char c : s) if (alphabet.find(c) != string::npos) wys[c]++;
    return wys;
}
double dlugosc_klucza(string s) {
    auto wys = wystapienia(s);
    double sum = 0;
    for (char c : alphabet) sum += (wys[c]*(wys[c]-1));
    int wszystkie = 0;
    for (char c : s) if (alphabet.find(c) != string::npos) wszystkie++;
    double out = sum/((wszystkie)*(wszystkie-1)*1.0);
    out = 0.0285/(out-0.0385);
    return round(out*100)/100.0;
}
int main() {
    //1
    ifstream dane1("dokad.txt");
    string s;
    getline(dane1, s);
    dane1.close();
    string w1 = vinegere(s, "LUBIMYCZYTAC");
    int tmp = 0;
    for (char c : s) if (alphabet.find(c) != string::npos) tmp++;
    int w1l = tmp/12;
    if (tmp % 12 != 0) w1l++;
    //2
    ifstream dane2("szyfr.txt");
    s = "";
    getline(dane2, s);
    string key;
    getline(dane2, key);
    string w2 = un_vinegere(s, key);
    //3
    auto w3w = wystapienia(s);
    double w3k = dlugosc_klucza(s);
    dane2.close();
    ofstream wynik("Vigenere_wyniki.txt");
    wynik << "77.1\nIlosc powtorzen klucza: " << w1l << "\n\n" << w1 << "\n";
    wynik << "77.2\nOdszyfrowany tekst: " << w2 << "\n";
    wynik << "77.3\nWystapnienia:\n";
    for (char c : alphabet) wynik << c << ": " << w3w[c] << "\n";
    wynik << "Szacowana dlugosc klucza: " << w3k << "\n";
    wynik << "Rzeczywista dlugosc klucza: " << key.length();
    wynik.close();
    return EXIT_SUCCESS; 
}