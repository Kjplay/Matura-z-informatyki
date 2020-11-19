#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
bool zad1(string a, string b) {
    if (a.length() > b.length()) return (b.length()*3==a.length());
    else return (a.length()*3==b.length());
}
string zad2(string a, string b) {
    if (a == b) return "";
    if (a.length() < b.length() && b.find(a) == 0) {
        string s = b.substr(a.length(), b.length()-a.length());
        return s;
    } else return "";
}
int zakonczenie(string a, string b) {
    int dl = a.length() < b.length() ? a.length() : b.length();
    int l = 0;
    for (int i=0; i < dl; i++) {
        if (a[a.length()-1-i] == b[b.length()-1-i]) l++;
        else break;
    }
    return l;
}
string split(string a, string separator = ", ") {
    string out = "";
    if (a.length() == 1) return a;
    for (int i=0; i < a.length()-1; i++) {
        out += a[i]+separator;
    }
    out += a[a.length()-1];
    return out;
}
int main() {
    int w1 = 0, w3l = 0;
    string w1f = "";
    vector <string> w2;
    vector <string> w3;
    ifstream dane("napisy.txt");
    string a, b;
    while(dane >> a >> b) {
        if (zad1(a, b)) {
            w1++;
            if (w1f == "") w1f = a+" "+b;
        }
        string l = zad2(a, b);
        if (l.length() > 0) w2.push_back(a+" "+b+" -> "+split(l));
        if (zakonczenie(a, b) > w3l) {
            w3.clear();
            w3l = zakonczenie(a, b);
            w3.push_back(a+" "+b);
        } else if (zakonczenie(a, b) == w3l) w3.push_back(a+" "+b);
    }
    dane.close();
    ofstream wynik("wyniki.txt");
    wynik << "72.1\nLiczba wierszy: " << w1 << "\nPierwsza para napisow: " << w1f << "\n";
    wynik << "72.2\n";
    for (string s : w2) wynik << s << "\n";
    wynik << "72.3\nMax dlugosc zakonczenia: " << w3l << "\nPary napisow:\n";
    for (string s : w3) wynik << s << "\n";
    wynik.close();
    return EXIT_SUCCESS;
}