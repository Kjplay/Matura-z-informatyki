#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

string szyfruj(string s, vector<int> key) {
    int n = key.size();
    for (int i=0; i < s.size(); i++) {
        swap(s[i], s[key[(i % n)]-1]);
    }
    return s;
}

string deszyfruj(string s, vector<int> key) {
    int n = key.size();
    for (int i=s.size()-1; i >= 0; i--) {
        swap(s[i], s[key[(i % n)]-1]);
    }
    return s;
}

int main() {
    vector <string> w1;
    string s, w2, w3;
    int x;
    vector <int> keyt;

    //1
    ifstream dane1("szyfr1.txt");
    for (int i=0; i < 6; i++) {
        dane1 >> s;
        w1.push_back(s);
    }
    for (int i=0; i < 50; i++) {
        dane1 >> x;
        keyt.push_back(x);
    }
    dane1.close();

    for (string &z : w1) z = szyfruj(z, keyt);
    ofstream wynik1("wyniki_szyfr1.txt");
    for (string z : w1) wynik1 << z << "\n";
    wynik1.close();

    //2
    ifstream dane2("szyfr2.txt");
    dane2 >> s;
    keyt.clear();
    for (int i=0; i < 15; i++) {
        dane2 >> x;
        keyt.push_back(x);
    }
    dane2.close();

    w2 = szyfruj(s, keyt);

    ofstream wynik2("wyniki_szyfr2.txt");
    wynik2 << w2;
    wynik2.close();

    //3
    ifstream dane3("szyfr3.txt");
    dane3 >> s;
    keyt = {6, 2, 4, 1, 5, 3};
    dane3.close();
    
    w3 = deszyfruj(s, keyt);
    
    ofstream wynik3("wyniki_szyfr3.txt");
    wynik3 << w3;
    wynik3.close();

    return EXIT_SUCCESS;
}