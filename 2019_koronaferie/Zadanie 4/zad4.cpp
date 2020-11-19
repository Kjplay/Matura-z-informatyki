#include <string>
#include <array>
#include <vector>
#include <fstream>
using namespace std;
const int N = 20; //długość i szerokość planszy
array<array<int, N>, N> plansza; //pojemnik na planszę
void wczytaj(string nazwa) {
    ifstream dane(nazwa);
    for (int i=0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dane >> ::plansza[i][j]; //:: odnosi się do zmiennej globalnej, a nie lokalnej - tu brak znaczenia
        }
    }
}
bool checkIndex(int i, int j) { //sprawdzamy czy gracz nie wyjechał za planszę -> i, j 0...N-1
    return (i >= 0 && i < N && j >= 0 && j < N);
}
int graj(string sekwencja) {
    int sum = 0;
    int i = 0, j = 0;
    //Liczyc pole startowe? - niejasne zadanie
    sum += plansza[i][j]; //dodajemy punkty startowe
    for (char c : sekwencja) { //Dla każdego ruchu
        if (c == 'N') i--;
        else if (c == 'S') i++;
        else if (c == 'W') j--;
        else if (c == 'E') j++;
        if (!checkIndex(i, j)) return -1; //dyskwalifikacja
        else sum += plansza[i][j]; //dodaj punkty
    }
    return sum;
}
int ciag_EW(string sekwencja) {
    int e = 0, cm = 0; //e - długość aktualnego ciągu, cm - długość maksymalnego ciągu
    for (char c : sekwencja) {
        if (c == 'N' || c == 'S') { //ruch góra/dół - przerwij ciąg
            if (e > cm) cm = e;
            e = 0;    
        }
        else if (c == 'W' || c == 'E') e++; //ok, zwiększ ciąg
    }
    if (e > cm) cm = e; //jezeli ciag konczy sie wraz z sekwencja
    return cm;
}
int main() {
    int w1 = 0, w2g, w2m = 0, w3r = 0;
    vector <int> w3g;
    wczytaj("plansza.txt"); //wczytaj planszę
    ifstream dane("robot.txt");
    int g = 0; //nr gracza
    string sekwencja;
    while (dane >> sekwencja) { //wczytuj po 1 graczu
        g++; //nr zaczynaja sie od 1
        int points = graj(sekwencja); //wynik gry
        if (points == -1) w1++; //licz zdyskfalifikowanych
        if (points > w2m) { //znajdź najwyższy wynik i nr tego gracza
            w2m = points;
            w2g = g;
        }
        int ciag = ciag_EW(sekwencja); //ciąg E/W
        if (ciag > w3r) { //nowy największy - usuń stare nr graczy
            w3r = ciag;
            w3g.clear();
            w3g.push_back(g);
        } else if (ciag == w3r) w3g.push_back(g); //kolejny gracz z największym ciągiem - dodaj go
    }
    dane.close();
    ofstream wynik("zadanie4.txt"); //wypisz wyniki
    wynik << "4.1\nGracze zdyskwalifikowani: " << w1 << "\n";
    wynik << "4.2\nGracz (jego nr) z najwyższą liczba punktow: " << w2g << "\nLiczba punktów: " << w2m << "\n";
    wynik << "\nUWAGA! Do startowej liczby punktów (0) dodawano liczbe punktow z pola startowego (" << plansza[0][0] << ") - Niejasne polecenie, wynik może być za duży o " << plansza[0][0] << "\n";
    wynik << "4.3\nNajdłuższy ciag w jednym wierszu: " << w3r << "\nGracz(e) (ich nr) z takim ciagiem: ";
    for (int g : w3g) wynik << g << " ";
    wynik << "\n\nUWAGA! zadanie 4.3 było liczone NIEZALEŻNIE od dyskwalifikacji (ciąg był liczony nawet jeżeli zawodnik został zdyskwalifikowany - brak informacji w poleceniu)\n";
    wynik.close();
    return EXIT_SUCCESS; 
}