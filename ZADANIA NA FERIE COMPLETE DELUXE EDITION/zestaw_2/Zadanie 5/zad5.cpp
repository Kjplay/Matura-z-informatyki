#include <fstream>
#include <array>
#include <iostream>
#include <windows.h>
using namespace std;
int count_neighbours(array <array <bool, 20>, 12> tab, int row, int col) {
    int n = 0;
    int r = row-1;
    if (r < 0) r = 11;
    for (int i=0; i < 3; i++) { //upper row
        int c = col-1+i;
        if (c < 0) c = 19;
        else if (c > 19) c = 0;
        if (tab[r][c] == true) n++;
    }
    r = row;
    for (int i=0; i < 3; i++) { //middle row
        if (i == 1) continue; //skip current cell
        int c = col-1+i;
        if (c < 0) c = 19;
        else if (c > 19) c = 0;
        if (tab[r][c] == true) n++;
    }
    r = row+1;
    if (r > 11) r = 0;
    for (int i=0; i < 3; i++) { //down row
        int c = col-1+i;
        if (c < 0) c = 19;
        else if (c > 19) c = 0;
        if (tab[r][c] == true) n++;
    }
    //cout << row << " " << col << " " << n << endl;
    return n;
}
array <array <bool, 20>, 12> pokolenie(array <array <bool, 20>, 12> tab) {
    array <array <bool, 20>, 12> out;
    for (int i=0 ; i < 12; i++) {
        for (int j=0; j < 20; j++) {
            int neighbours = count_neighbours(tab, i, j);
            bool alive = tab[i][j];
            if (alive == true && (neighbours == 2 || neighbours == 3)) out[i][j] = true;
            else if (alive == false && neighbours == 3) out[i][j] = true;
            else out[i][j] = false;
        }
    }
    return out;
}
void print_field(array <array <bool, 20>, 12> tab) {
    for (int i=0 ; i < 12; i++) {
        for (int j=0; j < 20; j++) {
            char c;
            if (tab[i][j] == true) c = 'X';
            else c = '.';
            cout << c;
        }
        cout << endl;
    }
}
int main() {
    ifstream dane;
    ofstream wynik;
    dane.open("gra.txt");
    wynik.open("wyniki_5.txt");
    if (!dane.good() && !wynik.good()) return 2;
    string line;
    array <array <bool, 20>, 12> field;
    for (int i=0; i < 12; i++) {
        dane >> line;
        //cout << line << endl;
        for (int j=0; j < 20; j++) {
            if (line[j] == 'X') field[i][j] = true;
            else field[i][j] = false;
        }
    }
    int p = 1, a = 0, n, z1 = -1, z2 = -1, z3p = -1, z3a = -1;
    array <array <bool, 20>, 12> old_field;
    for (int i=0; i < 100; i++) {
        a = 0;
        for (int i=0; i < 12; i++) {
            for (int j=0; j < 20; j++) {
                if (field[i][j] == true) a++;
            }
        }
        if (p == 2) z2 = a;
        if (p == 37) z1 = count_neighbours(field, 1, 18); //starts from zero -> 2-1, 19-1
        if (old_field == field) {
            z3p = p;
            z3a = a;
        }
        if (z1 != -1 && z2 != -1 && z3p != -1 && z3a != -1) break;
        old_field = field;
        field = pokolenie(field);
        p++;
    }
    wynik << "5.1" << endl;
    wynik << "Sasiedzi: " << z1 << endl;
    wynik << "5.2" << endl;
    wynik << "Zywe komorki: " << z2 << endl;
    wynik << "5.3" << endl;
    wynik << "W pokoleniu: " << z3p << ", zywe komorki: " << z3a << endl;
    return 0;
}
