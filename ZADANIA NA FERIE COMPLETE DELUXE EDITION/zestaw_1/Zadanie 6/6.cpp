#include <fstream>
#include <string>
#include <iostream>
//#include <limits>
using namespace std;
string szyfr(string str, int k, bool reverse = false) {
    while (k > 25) {
        k-= 26;
    }
    if (reverse) k *= -1;
    string out = "";
    for (int i=0; i < str.length(); i++) {
        char c = str[i] + k;
        if (c > 90) c -=26;
        else if (c < 65) c += 26;
        out += c;
    }
    return out;
}
bool czy_szyfr_ok(string a, string b) {
    int k = ((90 - a[0]) + (b[0] - 65)) + 1;
    while (k > 25) {
        k -= 26;
    }
    if (szyfr(a, k) == b) return true;
    else return false;
}
int main() {
    //6_1
    ifstream d1, d2, d3;
    ofstream w1, w2, w3;
    d1.open("dane_6_1.txt");
    w1.open("wyniki_6_1.txt");
    if (d1.good() && w1.good()) {
        string a;
        for (int i=0; i < 100; i++) {
            d1 >> a;
            w1 << szyfr(a, 107) << endl;
        }
    }
    d1.close();
    w1.close();
    //6_2
    cout << "6_2_LOG:" << endl;
    d2.open("dane_6_2.txt");
    w2.open("wyniki_6_2.txt");
    if (d2.good() && w2.good()) {
        string a;
        int k;
        for (int i=0; i < 3000; i++) {
            if (d2 >> a >> k) {
                w2 << szyfr(a, k, true) << endl;
                //cout << "linijka nr: " << i+1 << " " << a << " " << k << endl;
            } else {
                cout << "W linijce " << i+1 << " jest blad! Brak klucza/slowa!" << endl;
                d2.clear();
                //d2.ignore(numeric_limits<streamsize>::max(), '\n');
                w2 << "------ BLEDNE DANE! -------" << endl;
            }
        }
    }
    d2.close();
    w2.close();
    //6_3
    d3.open("dane_6_3.txt");
    w3.open("wyniki_6_3.txt");
    if (d3.good() && w3.good()) {
        string a, b;
        for (int i=0; i < 3000; i++) {
            d3 >> a >> b;
            if (!czy_szyfr_ok(a, b)) {
                w3 << a << endl;
            }
        }
    }
    d3.close();
    w3.close();
}
