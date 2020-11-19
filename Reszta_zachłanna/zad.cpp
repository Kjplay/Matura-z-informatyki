#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector <int> reszta_zachalnna(int ilosc, vector<int> nominaly) {
    int mon = 0;
    int reszta = 0;
    vector <int> monety;
    while (ilosc > 0) {
        if (ilosc >= nominaly[mon]) {
            ilosc -= nominaly[mon];
            monety.push_back(nominaly[mon]);
        } else {
            if (++mon >= nominaly.size()) return {-1};
        }
    }
    return monety;
}
int main(){
    vector<int> m;
    cout << "Podaj ilosc reszty do wydania: ";
    int ilosc; cin >> ilosc;
    cout << "Podaj ilosc roznych nominalow: ";
    int j; cin >> j;
    for (int i=0; i < j;i++) {
        cout << "Podaj nominal: ";
        int z; cin >> z;
        if (count(m.begin(), m.end(), z) != 0) {
            cout << "Taki nominal juz byl!\n";
            i--;
        } else m.push_back(z);
    }
    sort(m.begin(), m.end(), greater<int>());
    vector<int> r = reszta_zachalnna(ilosc, m);
    if (r[0] == -1) {
        cout << "Nie udalo sie wydac reszty. Sprobuj innych nominalow.\n";
        return EXIT_FAILURE;
    }
    for (int i : r) cout << i << " ";
    return EXIT_SUCCESS;
}