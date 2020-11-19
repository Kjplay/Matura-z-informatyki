#include <vector>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>
#define all(x) begin(x), end(x)
using namespace std;
vector <int> czynniki_pierwsze(unsigned n){
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
long long odwroc(long long n) {
    long long x = 0;
    while (n != 0) {
        x *= 10;
        int z = n % 10;
        x += z;
        n /= 10;
    }
    return x;
}
bool palindrom(long long a, long long b) {
    while (a != 0) {
        if (a % 10 != b % 10) return false;
        a /= 10;
        b /= 10;
    }
    return true;
}
long iloczyn_cyfr(long long a) {
    long il = 1;
    while (a != 0) {
        il *= a % 10;
        a /= 10;
    }
    return il;
}
int moc(long long a) {
    int k = 1;
    long il = iloczyn_cyfr(a);
    while (il >= 10) {
        k++;
        il = iloczyn_cyfr(il);
    }
    return k;
}
int main() {
    ifstream liczby;
    ofstream wynik;
    map <int, int> moce;
    liczby.open("liczby.txt");
    wynik.open("wyniki_liczby.txt");
    long long a;
    int ile_3 = 0, ile_p = 0;
    int mini=999999999, maxi=10;
    while(liczby >> a) {
        vector <int> czynniki;
        czynniki = czynniki_pierwsze(a);
        sort(all(czynniki));
        auto it = unique(all(czynniki));
        czynniki.erase(it, czynniki.end());
        if (czynniki.size() == 3) {
            bool ok = true;
            for (int i : czynniki) if (i % 2 == 0) ok = false;
            if (ok) ile_3++;
        }
        long long b = odwroc(a);
        long long z = a+b;
        if (palindrom(z, odwroc(z))) ile_p++;
        int x = moc(a);
        moce[x]++;
        if (x == 1 && a < mini) mini = a;
        else if (x == 1 && a > maxi) maxi = a;
    }
    wynik << "9.1" << endl;
    wynik << ile_3 << endl;
    wynik << "9.2" << endl;
    wynik << ile_p << endl;
    wynik << "9.3" << endl;
    wynik << "moc   liczba" << endl;
    for (int i=1; i <= 8; i++) {
        wynik << i << ":    "<< moce[i] << endl;
    }
    wynik << "Max z moca 1: " << maxi << endl;
    wynik << "Min z moca 1: " << mini << endl;
}
