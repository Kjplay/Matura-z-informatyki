#include <string>
#include <fstream>
#include <array>
#include <tuple>
#include <string>
#include <vector>
using namespace std;
const string A_KEY = "ALGORYTM";
tuple <string, int, array<int, 8>> skrot(string s) {
    array <int, 8> kody;
    for (int i=0; i < 8; i++) kody[i] = A_KEY[i];
    while (s.length() % 8 != 0) s += ".";
    for (int i=0; i < s.length()/8; i++) {
        for (int j=0 ; j < 8; j++) {
            kody[j] = (kody[j]+s[i*8+j]) % 128;
        }
    }
    string wynik = "";
    for (int j=0 ; j < 8; j++) {
        char c = 65 + (kody[j] % 26);
        wynik += c;
    }
    return {wynik, s.length(), kody};
}
string deszyfruj(vector <int> s, int d, int n) {
    string wynik = "";
    for (int i=0; i < s.size(); i++) {
        int x = s[i]*d % n;
        char c = x;
        wynik += c;
    }
    return wynik;
}
int main() {
    ifstream dane("wiadomosci.txt");
    array <string, 11> wiad;
    array <vector <int>, 11> podpisy;
    for (int i=0; i < 11; i++) {
        getline(dane, wiad[i]);
    } 
    auto [w1, w1l, w1b] = skrot(wiad[0]);
    dane.close();
    ifstream dane2("podpisy.txt");
    for (int i=0; i < 11; i++) {
        for (int j=0; j < 8; j++) {
            int t; dane2 >> t;
            podpisy[i].push_back(t);
        }
    }
    dane2.close();
    vector <string> w2;
    for (auto v : podpisy) w2.push_back(deszyfruj(v, 3, 200));
    vector <int> w3;
    for (int i=0; i < 11; i++) if (get<0>(skrot(wiad[i])) == deszyfruj(podpisy[i], 3, 200)) w3.push_back(i+1);
    ofstream wynik("epodpis_wyniki.txt");
    wynik << "78.1\nLiczba znakow: " << w1l << "\n8 bajtow: ";
    for (int i : w1b) wynik << i << " ";
    wynik << "\nSkrot: " << w1 << "\n";
    wynik << "78.2\nSkroty: \n";
    for (string s : w2) wynik << s << "\n";
    wynik << "78.3\nWiarygodne: ";
    for (int i : w3) wynik << i << " ";
    wynik.close();
    return EXIT_SUCCESS;
}