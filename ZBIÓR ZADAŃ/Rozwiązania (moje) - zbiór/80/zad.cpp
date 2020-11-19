#include <vector>
#include <fstream>
#include <array>
#include <algorithM>
#include <cmath>
#define all(x) begin(x), end(x)
using namespace std;
using trojkat = array<int, 3>;
bool czy_trojkat(trojkat t) {
    sort(all(t));
    return t[0]+t[1] > t[2];
}
bool prostokatny(trojkat t) {
    sort(all(t));
    return pow(t[0], 2)+pow(t[1], 2) == pow(t[2], 2);
}
int obwod(trojkat t) {
    return t[0]+t[1]+t[2];
}
int main() {
    vector <int> trojkaty;
    vector <trojkat> w1;
    int w2 = 0, w3 = 0;
    ifstream dane("dane_trojkaty.txt");
    int x;
    while(dane >> x) trojkaty.push_back(x);
    dane.close();
    for (int i=2; i < trojkaty.size(); i++) {
        trojkat t{trojkaty[i-2], trojkaty[i-1], trojkaty[i]};
        if (prostokatny(t)) w1.push_back(t);
    }
    for (int i=0; i < trojkaty.size(); i++) {
        for (int j=i+1; j < trojkaty.size(); j++) {
            for (int k=j+1; k < trojkaty.size(); k++) {
                trojkat t{trojkaty[i], trojkaty[j], trojkaty[k]};
                if (czy_trojkat(t)) {
                    w3++;
                    int o = obwod(t);
                    if (o > w2) w2 = o;
                }
            }
        }
    }
    ofstream wynik("wyniki_trojkaty.txt");
    wynik << "80.1 Wszystkie trojki:\n";
    for (auto t : w1) wynik << "(" << t[0] << ", " << t[1] << ", " << t[2] << ")\n";
    wynik << "80.2\nNajwiekszy obwod: " << w2 << "\n";
    wynik << "80.3\nTrojkaty nieprzystajace: " << w3;
    wynik.close();
    return EXIT_SUCCESS;
}
