#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#define all(x) begin(x), end(x)
using namespace std;
int zly(vector<int> c) {
    vector <int> roznice;
    for (int i=1 ; i<c.size(); i++) {
        roznice.push_back(c[i]-c[i-1]);
    }
    vector <int> kopia = roznice;
    sort(all(kopia));
    auto it = unique(all(kopia));
    kopia.erase(it, kopia.end());
    for (int i : kopia) cout << i << " ";
    cout << " -> ";
    int x1, x2;
    vector<int>::iterator it1;
    vector<int>::iterator it2;
    if (count(all(roznice), kopia[0]) > 1) {
        cout << 1 << "\n";
        it1 = find(all(roznice), kopia[1]);
        if (kopia.size() > 2) it2 = find(all(roznice), kopia[2]);
        x1 = distance(roznice.begin(), it1);
        if (kopia.size() > 2) x2 = distance(roznice.begin(), it2);
        else x2 = x1+1;

    } else if (count(all(roznice), kopia[1]) > 1) {
        cout << 2 << "\n";
        it1 = find(all(roznice), kopia[0]);
        if (kopia.size() > 2) it2 = find(all(roznice), kopia[2]);
        x1 = distance(roznice.begin(), it1);
        if (kopia.size() > 2) x2 = distance(roznice.begin(), it2);
        else x2 = x1+1;
    } else {
        cout << 3 << "\n";
        it1 = find(all(roznice), kopia[1]);
        it2 = find(all(roznice), kopia[0]);
        x1 = distance(roznice.begin(), it1);
        x2 = distance(roznice.begin(), it2);
    }
    int pos = x1 > x2 ? x1 : x2;
    return c[pos];
} 
int main() {
    ifstream dane("bledne.txt");
    vector <int> w3;
    int a;
    while (dane >> a) {
        vector <int> ciag;
        for (int i=0 ; i < a ; i++) {
            int x; dane >> x;
            ciag.push_back(x);
        }
        w3.push_back(zly(ciag));
    }
    dane.close();
    ofstream wynik("wyniki3.txt");
    for (int i : w3) wynik << i << "\n";
    wynik.close();
    return EXIT_SUCCESS;
}