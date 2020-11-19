#include <vector>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>
#define all(x) begin(x), end(x)
using namespace std;
const int N = 1095;
using dane_s = vector<pair<long int, long int>>;
long int horner(vector<int> wspl, int x) {
    long int a = wspl[0];
    for(int i=1; i < wspl.size(); i++) {
        a = a*x + wspl[i];
    }
    return a;
}
vector <int> rozdziel(long long a) {
    vector <int> v;
    if (a == 0) v.push_back(a);
    while (a > 0) {
        v.push_back(a % 10);
        a /= 10;
    }
    reverse(all(v));
    return v;
}
long long zlacz(vector<int> v) {
    long long t = 1;
    long long out = 0;
    for (int i=v.size()-1;i >=0; i--) {
        out += v[i]*t;
        t *= 10;
    }
    return out;
}
int XtoDec(long long a, int base) {
    bool u = (a < 0);
    if (u) a *= -1;
    long long o =  horner(rozdziel(a), base);
    if (u) o *= -1;
    return o;
}
long long DectoX(long int a, int base) {
    bool u = (a < 0);
    if (u) a *= -1;
    vector<int> v;
    while (a > 0) {
        v.push_back(a % base);
        a /= base;
    }
    reverse(all(v));
    a = zlacz(v);
    if (u) a *= -1;
    return a;
}
int skok(int ti, int tj, int i, int j) {
    int r = pow(ti-tj, 2);
    double x = (r*1.0)/(abs(i-j)*1.0);
    return ceil(x);
}
int max_skok(vector<long int> pomiary) {
    int maxi = 0;
    for (int i=0; i < pomiary.size(); i++) {
        for (int j=i+1; j < pomiary.size(); j++) {
            int t = skok(pomiary[i], pomiary[j], i, j);
            if (t > maxi) maxi = t;
        }
    }
    return maxi;
}
vector <long int> separateRow(dane_s d, int row) {
    vector <long int> out;
    if (row == 1) {
        for (pair <int, int> p : d) {
            out.push_back(p.first);
        }
    } else {
        for (pair <int, int> p : d) {
            out.push_back(p.second);
        }
    }
    return out;
}
bool time_bad(int time, int day) {
    return time != (12+((day-1)*24));
}
int main() {
    ifstream d1("dane_systemy1.txt");
    ifstream d2("dane_systemy2.txt");
    ifstream d3("dane_systemy3.txt");
    dane_s s1, s2, s3;
    long long t1, t2, t3, z1, z2, z3; //t - temperatura, z - zegar
    int m1  = 9999999, m2  = 9999999, m3  = 9999999;
    int r1  = -9999999, r2  = -9999999, r3  = -9999999;
    int w2 = 0, w3 = 0;
    for (int i=0; i < N; i++) {
        bool tok1, tok2, tok3, rr1 = false, rr2 = false, rr3 = false;
        //S1
        d1 >> z1 >> t1;
        z1 = XtoDec(z1, 2); t1 = XtoDec(t1, 2);
        if (t1 < m1) {
            m1 = t1;
        } //mini
        tok1 = time_bad(z1, i+1); //time
        if (t1 > r1) { //rekord temper
            r1 = t1;
            rr1 = true;
        }
        s1.push_back(pair<int, int>{z1, t1});
        //S2
        d2 >> z2 >> t2;
        z2 = XtoDec(z2, 4); t2 = XtoDec(t2, 4);
        if (t2 < m2) m2 = t2; //mini
        tok2 = time_bad(z2, i+1); //time
        if (t2 > r2) { //rekord temper
            r2 = t2;
            rr2 = true;
        }
        s2.push_back(pair<int, int>{z2, t2});
        //S3
        d3 >> z3 >> t3;
        z3 = XtoDec(z3, 8); t3 = XtoDec(t3, 8);
        if (t3 < m3) m3 = t3; //mini
        tok3 = time_bad(z3, i+1); //time
        if (t3 > r3) { //rekord temper
            r3 = t3;
            rr3 = true;
        }
        s3.push_back(pair<int, int>{z3, t3});
        if (tok1 && tok2 && tok3) w2++;
        if (rr1 || rr2 || rr3) w3++;
    }
    int w4 = max_skok(separateRow(s1, 2));
    d1.close(); d2.close(); d3.close();
    ofstream wynik("wyniki_systemy.txt");
    wynik << "58.1\n1: " << DectoX(m1, 2) << "\n2: " << DectoX(m2, 2) << "\n3: " << DectoX(m3, 2) << "\n";
    wynik << "58.2\n" << w2 << "\n";
    wynik << "58.3\n" << w3 << "\n";
    wynik << "58.4\n" << w4;
    wynik.close();
    return EXIT_SUCCESS;
}