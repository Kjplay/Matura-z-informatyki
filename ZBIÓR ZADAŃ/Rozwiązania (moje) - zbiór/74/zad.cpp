#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
#define all(x) begin(x), end(x)
using namespace std;
const string Numeric = "0123456789";
const string UpperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string LowerCase = "abcdefghijklmnopqrstuvwxyz";
int type(char c) {
    for (char s : Numeric) if (s == c) return 0; //numeric
    for (char s : UpperCase) if (s == c) return 1; //upper
    for (char s : LowerCase) if (s == c) return 2; //lower
    return 3;
}
bool zad1(string s) {
    for (char c : s) if (type(c) != 0) return false;
    return true;
}
bool check_four(string s) {
    sort(all(s));
    for (int i=1; i < s.length(); i++) if (s[i]-s[i-1] != 1) return false;
    return true;
}
bool zad3(string s) {
    if (s.length() < 4) return false;
    for (int i=0; i < s.length()-3; i++) if (check_four(s.substr(i, 4))) return true;
    return false;
}
bool zad4(string s) {
    bool n = false, u = false, l = false;
    for (char c : s) {
        switch (type(c)) {
        case 0: //numeric
            n = true;
            break;
        case 1:
            u = true;
            break;
        case 2:
            l = true;
            break;
        default: //prevent crashing when code 3
            break;
        }
        if (n && u && l) return true;
    }
    return false;
}
int main() {
    ifstream dane("hasla.txt");
    string s;
    int w1 = 0, w3 = 0, w4 = 0;
    map <string, int> w2;
    while (dane >> s) {
        if (zad1(s)) w1++;
        w2[s]++;
        if (zad3(s)) w3++;
        if (zad4(s)) w4++;
    }
    dane.close();
    ofstream wynik("wyniki_hasla.txt");
    wynik << "74.1\n" << w1 << "\n";
    wynik << "74.2\n";
    for (pair<string, int> p : w2) {
        if (p.second > 1) wynik << p.first << "\n";
    }
    wynik << "74.3\n" << w3 << "\n";
    wynik << "74.4\n" << w4;
    wynik.close();
    return EXIT_SUCCESS;
}