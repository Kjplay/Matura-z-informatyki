#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <iostream>
using namespace std;

vector <int> fibonacci(int il) {
    vector <int> out;
    if (il >= 1) out.push_back(1);
    if (il >= 2) out.push_back(1);
    for (int i=2; i < il; i++) { //indeksy od 0
        int sum = out[i-2]+out[i-1];
        out.push_back(sum);
    }
    return out;
}

bool liczba_pierwsza(int n) {
    for (int i=2; i*i <= n; i++) if (n%i == 0) return false;
    return true;
}
string dec_to_bin_string(int n) {
    vector <string> out;
    while (n > 0) {
        int t = n%2;
        out.push_back(to_string(t));
        n /= 2;
    }
    reverse(out.begin(), out.end());
    string s = "";
    for (string i : out) s += i;
    return s;
}

vector <string> convert_binary(vector <int> dane) {
    vector <string> out;
    for (int i : dane) {
        out.push_back(dec_to_bin_string(i));
    }
    int max_len = out[out.size()-1].size();
    for (int i = out.size()-2; i >= 0; i--) {
        string s = "";
        for (int j=0 ; j < max_len-out[i].size(); j++) s += "0";
        out[i] = s + out[i];
    }
    return out;
}
int main() {
    ofstream wynik("wyniki.txt");
    vector <int> dane = fibonacci(40);
    array<int, 4> w1{dane[9], dane[19], dane[29], dane[39]}; //indeksy od 0
    vector <int> w2_p;
    vector <int> w2_n;
    for (int i=2 ; i<dane.size(); i++) { //w pierwsze liczby to 1
        if (liczba_pierwsza(dane[i])) {
            w2_p.push_back(dane[i]);
            w2_n.push_back(i+1);
        }
    }
    vector <string> w3 = convert_binary(dane);
    vector <string> w4;
    for (int i : dane) {
        string t = dec_to_bin_string(i);
        if (count(t.begin(), t.end(), '1') == 6) {
            w4.push_back(t);
        }
    }
    
    wynik << "1\n";
    for (int i=0; i < 4; i++) {
        wynik << (i+1)*10 << ". " << w1[i] << "\n";
    }
    wynik << "2\n";
    for (int i=0; i < w2_p.size(); i++) {
        wynik << w2_n[i] << ". " << w2_p[i] << "\n";
    }
    wynik << "3\n";
    for (string s : w3) wynik << s << "\n";
    wynik << "W pliku: \"fraktal.xlsx\"\n";
    wynik << "4\n";
    for (string s : w4) wynik << s << "\n";
}