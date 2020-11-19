#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;
const string MUTACJA = "BCDDC";
vector <string> geny(string s) {
    vector <string> out;
    int pos = 0;
    size_t f;
    while (true) {
        f = s.find("AA", pos);
        if (f != string::npos) {
            int begin = f;
            f = s.find("BB", f+2);
            if (f != string::npos) {
                out.push_back(s.substr(begin, f-begin+2));
                pos = f+2;
            } else return out;
        } else return out;
    }
}

string sumuj_vector(vector <string> v) {
    string out = "";
    for (string s : v) out += s;
    return out;
}

int dlugi_gen(vector <string> v) {
    int m = 0;
    for (string s : v) if (s.length() > m) m = s.length();
    return m;
}
bool czy_mutacja(vector <string> v) {
    for (string s : v) if (s.find(MUTACJA) != string::npos) return true;
    return false;
}
int main() {
    ifstream dane("dane_geny.txt");
    ofstream wynik("wyniki_geny.txt");
    map <int, int> gatunki;
    string s;
    int w1g = 0, w1m = 0, w2 = 0, w3g = 0, w3m = 0, w4o = 0, w4s = 0;
    while (dane >> s) {
        gatunki[s.length()]++;
        vector <string> gen = geny(s);
        if (gen.size() > w3g) w3g = gen.size();
        if (dlugi_gen(gen) > w3m) w3m = dlugi_gen(gen);
        if (czy_mutacja(gen)) w2++;
        string old = s;
        string sum_geny = sumuj_vector(gen);
        reverse(s.begin(), s.end());
        if (old == s) w4s++;
        string kod = sumuj_vector(geny(s));
        if (kod == sum_geny) w4o++;
    }
    dane.close();
    for (pair <int, int> p : gatunki) {
        w1g++;
        if (p.second > w1m) w1m = p.second;
    }
    wynik << "69.1\nGatunki: " << w1g << "\nMax osobniki tego samego: " << w1m << "\n";
    wynik << "69.2\n" << w2 << "\n";
    wynik << "69.3\nMax geny u jednego: " << w3g << "\nMax dlugosc genu: " << w3m << "\n";
    wynik << "69.4\nOdporne: " << w4o << "\nSilnie odporne: " << w4s;
    wynik.close();
    return 0;
}