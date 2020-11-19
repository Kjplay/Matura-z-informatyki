#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
vector <int> rozdziel(int n) {
    vector <int> out;
    while (n > 0) {
        out.push_back(n % 10);
        n /= 10;
    }
    reverse(out.begin(), out.end());
    return out;
}
int horner(vector <int> wspl, int x) {
    int out = wspl[0];
    for (int i=1; i < wspl.size(); i++) {
        out = (out*x) + wspl[i];
    }
    return out;
}
int dec_to_oct(int n) {
    vector <int> reszty;
    while (n > 0) {
        int temp = n % 8;
        reszty.push_back(temp);
        n /= 8;
    }
    int x = 1;
    int out = 0;
    for (int i=reszty.size()-1; i >= 0; i--) {
        out += reszty[i]*x;
        x *= 10;
    }
    return out;
}
int oct_to_dec(int n) {
    return horner(rozdziel(n), 8);
}
int licz_6(int n) {
    vector <int> tab = rozdziel(n);
    return count(tab.begin(), tab.end(), 6);
}
int octalToDecimal(int octalNumber)
{
    int decimalNumber = 0, i = 0, rem;
    while (octalNumber != 0)
    {
        rem = octalNumber % 10;
        octalNumber /= 10;
        decimalNumber += rem * pow(8, i);
        ++i;
    }
    return decimalNumber;
}
int main() {
    ifstream liczby1("liczby1.txt");
    ifstream liczby2("liczby2.txt");
    ofstream wyniki("wyniki.txt");
    int oct, dec, old_dec, same = 0, octb = 0, dec6 = 0, oct6 = 0;
    int maxh = -1, minh = -1, ciag1 = -1, ciagd = 1, ciagdm = 0, ciag1m;
    for (int i=0; i<1000;i++) {
        liczby1 >> oct;
        liczby2 >> dec;
        if (oct > maxh || maxh == -1) maxh = oct;
        if (oct < minh || minh == -1) minh = oct;
        if (i == 0) ciag1 = dec;
        else {
            if (old_dec <= dec) {
                ciagd++;
            } else {
                if (ciagdm < ciagd) {
                    ciag1m = ciag1;
                    ciagdm = ciagd;
                }
                ciag1 = dec;
                ciagd = 1;
            }
        }
        old_dec = dec;
        if (octalToDecimal(oct) == dec) same++;
        else if (oct_to_dec(oct) > dec) octb++;
        dec6 += licz_6(dec);
        oct6 += licz_6(dec_to_oct(dec));
    }
    //jezeli ciag konczy sie razem z plikiem
    if (ciagdm < ciagd) {
        ciag1m = ciag1;
        ciagdm = ciagd;
    }
    wyniki << "Podpunkt 1\n\n";
    wyniki << "Max: " << maxh << "\n" << "Min: " << minh << "\n\n";
    wyniki << "Podpunkt 2\n\n";
    wyniki << "Dlugosc ciagu: " << ciagdm << ", 1szy element: " << ciag1m << "\n\n";
    wyniki << "Podpunkt 3\n\n";
    wyniki << "Takie same: " << same << ", 1 > 2: " << octb << "\n";
    wyniki << "UWAGA: Wartość takich samych - 639 w kluczu jest BŁĘDNA - wpisali tu odpowiedz z podpunktu 2\nZalaczylem plik z rozwiazania, ktory rowniez daje 160\n\n";
    wyniki << "Podpunkt 4\n\n";
    wyniki << "6stki w dziesietnym: " << dec6 << "\n";
    wyniki << "6stki w osemkowym: " << oct6 << "\n";
}

