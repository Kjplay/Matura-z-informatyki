#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ifstream dane("liczby.txt");
    ofstream wynik("wyniki_liczby.txt");
    int a, tys = 0, tys1 = -1, tys2 = -1, d = 0, maxip = 0;
    vector <int> uzyte;
    vector <int> d18;
    map <int, vector <int> > dzielniki;
    while(dane >> a) {
        int dziel = 0;
        dzielniki[a].clear();
        if (a < 1000) {
            tys++;
            swap(tys1, tys2);
            tys1 = a;
        }
        for (int i=1;i <= a/2;i++) {
            if (a % i == 0) {
                dziel++;
                dzielniki[a].push_back(i);
            }
        }
        dziel++; //liczymy samo a
        dzielniki[a].push_back(a);
        if (dziel == 18) {
            d++;
            if (count(d18.begin(), d18.end(), a) == 0) {
                d18.push_back(a);
            }
        }
        if (count(uzyte.begin(), uzyte.end(), a) == 0) {
            uzyte.push_back(a);
        }
    }
    for (int i=0; i < uzyte.size(); i++) {
        bool ok = true;
        for (int j=0; j < uzyte.size(); j++) {
            if (j == i) continue;
            for (int k=0; k < dzielniki[uzyte[i]].size();k++) {
                if (dzielniki[uzyte[i]][k] != 1) {
                    if (count(dzielniki[uzyte[j]].begin(), dzielniki[uzyte[j]].end(), dzielniki[uzyte[i]][k]) != 0) ok = false;
                }
            }
        }
        if (ok && uzyte[i] > maxip) maxip = uzyte[i];
    }
    wynik << "6.1" << endl;
    wynik << "Ilosc: " << tys << endl << "Dwie ostatnie: " << tys1 << " " << tys2 << endl;
    wynik << "6.2" << endl;
    for (int i=0; i < d18.size(); i++) {
        wynik << "Liczba " << d18[i] << " i jej dzielniki: ";
        for (int j=0; j < dzielniki[d18[i]].size(); j++) {
            wynik << dzielniki[d18[i]][j] << " ";
        }
        wynik << endl;
    }
    wynik << "6.3" << endl;
    wynik << maxip << endl;
}
