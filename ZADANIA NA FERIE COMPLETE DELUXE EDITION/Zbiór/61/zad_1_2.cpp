#include <fstream>
#include <tuple>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
tuple <bool, int> arytmetyczny(vector <int> c) {
    if (c.size() >= 2) {
        int r = c[1] - c[0];
        for (int i=1; i<c.size(); i++) {
            if (c[i] - c[i-1] != r) return {false, 0};
        }
        return {true, r};
    } else return {false, 0};
}
bool cubic_root(int c) {
    double x = cbrt(c);
    return (x == round(x));
}
int main() {
    ifstream dane("ciagi.txt");
    int a, w1 = 0, w1r = -1;
    vector <int> w2;
    while (dane >> a) {
        vector <int> ciag;
        int sz_max = -1;
        for (int i=0; i < a; i++) {
            int x; dane >> x;
            ciag.push_back(x);
            if (cubic_root(x)) w2.push_back(x);
        }
        auto [ar, roz] = arytmetyczny(ciag);
        if (ar) {
            w1++;
            if (roz > w1r) w1r = roz;
        }
    }
    dane.close();
    ofstream wynik1("wynik1.txt");
    wynik1 << "Ciagi arytmetyczne: " << w1 << "\nNajwieksza roznica: " << w1r;
    wynik1.close();
    ofstream wynik2("wynik2.txt");
    for (int i : w2) wynik2 << i << "\n";
    wynik2.close();
    return EXIT_SUCCESS;
}