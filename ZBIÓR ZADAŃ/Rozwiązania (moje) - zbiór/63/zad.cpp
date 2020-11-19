#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector <int> czynniki_pierwsze(unsigned int n){
    vector <int> c;
    for(int i = 2; i*i <= n; i++){
        while(n % i == 0){
            c.push_back(i);
            n /= i; 
        }
        if(n == 1){
            return c;
        }
    }
    c.push_back(n);
    return c;
}
bool dwuckyliczny(string s) {
    if (s.length() % 2 == 1) return false;
    if (s.substr(0, s.length()/2) == s.substr(s.length()/2, s.length()/2)) return true;
    else return false;
}
bool bez_jedynki_obok(string s) {
    for (int i=1; i < s.size(); i++) {
        if (s[i] == '0') i++;
        else if (s[i-1] == '1') return false;
    }
    return true;
}
int main() {
    string temp;
    ifstream dane("ciagi.txt");
    ofstream wyniki("wyniki_ciagi.txt");
    vector < string > wynik1;
    unsigned int wynik2 = 0, wynik3max = -1, wynik3min = -1, wynik3ile = 0;
    while (dane >> temp) {
        if (temp == "") break;
        if (dwuckyliczny(temp)) wynik1.push_back(temp);
        if (bez_jedynki_obok(temp)) wynik2++;
        vector <int> temp_czynniki;
        unsigned int temp_liczba = stoi(temp, nullptr, 2);
        temp_czynniki = czynniki_pierwsze(temp_liczba);
        if (temp_czynniki.size() == 2) {
            wynik3ile++;
            if (temp_liczba < wynik3min || wynik3min == -1) wynik3min = temp_liczba;
            if (temp_liczba > wynik3max || wynik3max == -1) wynik3max = temp_liczba;
        }
    }
    dane.close();
    wyniki << "63.1\nCiagi dwucykilczne: \n";
    for (string s : wynik1) wyniki << s << "\n";
    wyniki << "63.2\nCiagi bez dwoch jedynek obok siebie: " << wynik2 << "\n";
    wyniki << "63.3\nIlosc liczb polpierwszych: " << wynik3ile << "\n";
    wyniki << "Najwieksza liczba polpierwsza: " << wynik3max << "\n";
    wyniki << "Najmniejsza liczba polpierwsza: " << wynik3min << "\n";
    wyniki.close();
    return 0;
}