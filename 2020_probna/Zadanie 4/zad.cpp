#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
using namespace std;
bool is_zero(int n) {
    return n == 0;
}
int gra(map <int, vector <int>> tarcze, vector <int> strzaly, int czas = 300, bool czy_chowaja = true) {
    vector <int> aktywne;
    int punkty = 0;
    for (int i=1; i <= czas; i++) {
        aktywne.insert(aktywne.end(), tarcze[i].begin(), tarcze[i].end());
        if (count(strzaly.begin(), strzaly.end(), i) != 0) {
            punkty += aktywne.size();
            if (czy_chowaja == true) aktywne.clear();
        }
        for (int &y : aktywne) y--;
        remove_if(aktywne.begin(), aktywne.end(), is_zero);
        aktywne.shrink_to_fit(); //resize vector to save memory
    }
    return punkty;
}
int zlota_sekunda(map <int, vector <int>> tarcze, int czas = 300) {
    vector <int> aktywne;
    int gold = 0;
    for (int i=1; i <= czas; i++) {
        aktywne.insert(aktywne.end(), tarcze[i].begin(), tarcze[i].end());
        if (aktywne.size() > gold) gold = aktywne.size();
        for (int &y : aktywne) y--;
        remove_if(aktywne.begin(), aktywne.end(), is_zero);
        aktywne.shrink_to_fit(); //resize vector to save memory
    }
    return gold;
}
int main() {
    ifstream dane("festyn.txt");
    ofstream wynik("zadanie4.txt");
    vector <int> wyniki1;
    vector <int> wyniki2;
    vector <int> wyniki3;
    vector <int> wyniki4;
    for (;;) {
        int x;
        dane >> x;
        if (!dane.fail()) {
            int max_widocznosc = 0;
            map <int, vector <int>> tarcze;
            while (x-- > 0) {
                int a, b;
                dane >> a >> b;
                tarcze[a].push_back(b);
                if (b > max_widocznosc) max_widocznosc = b;
            }
            wyniki2.push_back(max_widocznosc);
            vector <int> strzaly;
            dane >> x;
            while (x-- > 0) {
                int a;
                dane >> a;
                strzaly.push_back(a);
            }
            wyniki1.push_back(gra(tarcze, strzaly));
            wyniki3.push_back(zlota_sekunda(tarcze));
            wyniki4.push_back(gra(tarcze, strzaly, 300,  false));
        } else break;
    }
    vector < vector<int> > odpowiedzi{wyniki1, wyniki2, wyniki3, wyniki4};
    for (int i=0; i < odpowiedzi.size(); i++) {
        wynik << "4." << i+1 << "\n";
        for (int y = 0; y < odpowiedzi[i].size(); y++) {
            wynik << "Zestaw " << y+1 << ": " << odpowiedzi[i][y] << "\n";
        }
        wynik << "\n";
    }
}