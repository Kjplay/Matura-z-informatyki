#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
const int ROW_SIZE = 20;
typedef array < array <bool, ROW_SIZE>, ROW_SIZE > matryca;
typedef array <bool, ROW_SIZE> bit_array;
typedef array < array <bool, ROW_SIZE/2>, ROW_SIZE/2> sub_matryca;
struct bity {
    bit_array row;
    bit_array col;
};
struct quad {
    sub_matryca one;
    sub_matryca two;
    sub_matryca three;
    sub_matryca four;
};
struct obrazek {
    unsigned int nr_obrazka;
    matryca dane;
    bity par;
    vector <int> wrong_rows;
    vector <int> wrong_cols;
    unsigned short int state;
    array <int, 2> r_position;
    //functions
    int wrong_sum() {
        return wrong_rows.size()+wrong_cols.size();
    }
    bit_array getRow(unsigned int n) {
        bit_array out;
        for (int i=0; i < ROW_SIZE; i++) out[i] = this->dane[n-1][i];
        return out;
    }
    bit_array getCol(unsigned int n) {
        bit_array out;
        for (int i=0; i < ROW_SIZE; i++) out[i] = this->dane[i][n-1];
        return out;
    }
    sub_matryca getSubMat(unsigned int startRow, unsigned int startCol) {
        sub_matryca out;
        for (int i=startRow; i < startRow+(ROW_SIZE/2); i++) {
            for (int j=startCol; j < startCol+(ROW_SIZE/2); j++) {
                out[i-startRow][j-startCol] = this->dane[i][j];
            }
        }
        return out;
    }
    array <unsigned int, 2> count_pixels() {
        array <unsigned int, 2> pixels;
        int blacks = 0, whites = 0;
        for (int i=0; i < ROW_SIZE; i++) {
            for (int j=0 ; j < ROW_SIZE; j++) {
                if (this->dane[i][j] == false) whites++;
                else blacks++;
            }
        }
        pixels[0] = whites;
        pixels[1] = blacks;
        return pixels;
    }
    void print(ostream &s) {
        for (int i=0; i < ROW_SIZE; i++) {
            for (int j=0 ; j < ROW_SIZE; j++) {
                s << this->dane[i][j] << " ";
            }
            s << "\n";
        }
    }
};

typedef vector <obrazek> galeria;

galeria wczytaj(string nazwa_pliku) {
    ifstream dane(nazwa_pliku);
    galeria out;
    int nr = 1;
    int x = 200;
    while (x-- > 0) {
        obrazek obraz;
        obraz.nr_obrazka = nr;
        char temp;
        for (int i=0; i < ROW_SIZE; i++) {
            for (int j=0; j < ROW_SIZE; j++) {
                dane >> temp;
                if (temp == '1') obraz.dane[i][j] = true;
                else obraz.dane[i][j] = false;
            }
            dane >> temp;
            if (temp == '1') obraz.par.row[i] = true;
            else obraz.par.row[i] = false;
        }
        for (int i=0; i < ROW_SIZE; i++) {
            dane >> temp;
            if (temp == '1') obraz.par.col[i] = true;
            else obraz.par.col[i] = false;
        }
        out.push_back(obraz);
        string check;
        getline(dane, check);
        nr++;
    }
    dane.close();
    return out;
}
bool rekurencyjny(obrazek o) {
    quad t;
    t.one = o.getSubMat(0, 0);
    t.two = o.getSubMat(0, ROW_SIZE/2);
    t.three = o.getSubMat(ROW_SIZE/2, 0);
    t.four = o.getSubMat(ROW_SIZE/2, ROW_SIZE/2);
    return (t.one == t.two && t.one == t.three && t.one == t.four);
}
void obraz_state(obrazek &o) {
    int wrong_rows = 0, wrong_cols = 0;
    //check rows
    for (int i=1; i <= ROW_SIZE; i++) {
        bit_array temp;
        temp = o.getRow(i);
        int t = count(temp.begin(), temp.end(), true);
        if (t % 2 != o.par.row[i-1] ) {
            wrong_rows++;
            o.wrong_rows.push_back(i);
        }
    }
    //check cols
    for (int i=1; i <= ROW_SIZE; i++) {
        bit_array temp;
        temp = o.getCol(i);
        //cout << o.par.col[i];
        int t = count(temp.begin(), temp.end(), true);
        if (t % 2 != o.par.col[i-1]) {
            wrong_cols++;
            o.wrong_cols.push_back(i);
        }
    }
    if (wrong_rows == 0 && wrong_cols == 0) o.state =  0; // 0 -> ok
    else if (wrong_rows > 1 || wrong_cols > 1) o.state = 2; //2 -> bad
    else o.state = 1; //1 -> to repair
}
void repair(obrazek &o) {
    if (o.wrong_sum() == 2) {
        o.r_position[0] = o.wrong_rows[0];
        o.r_position[1] = o.wrong_cols[0];
    } else {
        if (o.wrong_rows.size() == 1) {
            o.r_position[0] = o.wrong_rows[0];
            o.r_position[1] = ROW_SIZE+1;
        } else {
            o.r_position[1] = o.wrong_cols[0];
            o.r_position[0] = ROW_SIZE+1;
        }
    }
}
int main() {
    galeria obrazy;
    obrazy = wczytaj("dane_obrazki.txt");
    ofstream wynik("wyniki_obrazki.txt");
    int wynik1 = 0, wynik1max = 0, wynik2ile = 0, wynik3ok = 0, wynik3rep = 0, wynik3bad = 0, wynik3max = 0;
    bool wynik2czy = false;
    obrazek wynik2;
    for (obrazek &obraz : obrazy) {
        cout << "Przetwarzam obraz " << obraz.nr_obrazka << "\n";
        array <unsigned int, 2> pixels;
        pixels = obraz.count_pixels();
        if (pixels[0] < pixels[1]) wynik1++;//whites < blacks
        if (pixels[1] > wynik1max) wynik1max = pixels[1];
        if (rekurencyjny(obraz)) {
            wynik2ile++;
            if (!wynik2czy) {
                wynik2 = obraz;
                wynik2czy = true;
            }
        }
        obraz_state(obraz);
        if (obraz.state == 0) wynik3ok++;
        else if (obraz.state == 2) {
            wynik3bad++;
            if (obraz.wrong_sum() > wynik3max) wynik3max = obraz.wrong_sum();
        }
        else {
            wynik3rep++;
            repair(obraz);
        }
    }
    wynik << "6.1\n";
    wynik << "Rewersy: " << wynik1 << "\nMax czarnych: " << wynik1max << "\n";
    wynik << "6.2\n";
    wynik << "Obrazki rekurencyjne: " << wynik2ile << "\n";
    wynik2.print(wynik);
    wynik << "6.3\nPoprawne: " << wynik3ok << "\nNaprawialne: " << wynik3rep << "\nNienaprawialne: " << wynik3bad << "\n";
    wynik << "6.4 [Nr obrazka -> wiersz, kolumna]\n";
    for (obrazek &obraz : obrazy) {
        if (obraz.state == 1) {
            wynik << obraz.nr_obrazka << " -> " << obraz.r_position[0] << ", " << obraz.r_position[1] << "\n";
        }
    }
    wynik.close();
    return 0;
}
