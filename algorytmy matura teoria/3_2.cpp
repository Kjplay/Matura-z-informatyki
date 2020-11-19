#include <iostream>
#include <vector>
#include <array>
using namespace std;
int main() {
    vector <int> sumy;
    vector <array<int, 2>> pary;
    int n, a, b;
    cout << "Podaj n: ";
    cin >> n;
    int k[n+1];
    int p[n+1];
    p[0] = 0;
    for (int i=1;i <= n; i++) {
        cout << "Podaj " << i << " liczbe ciagu k: ";
        cin >> k[i];
        p[i] = p[i-1]+k[i];
    }
    int m;
    cout << "Podaj liczbe zapytan: ";
    cin >> m;
    for (int i=1; i <= m; i++) {
        cout << "Podaj a" << i << " oraz b" << i << ": ";
        cin >> a;
        cin >> b;
        array <int, 2> para;
        para[0] = a;
        para[1] = b;
        if (a > b) {
            int tmp = para[0];
            para[1] = para[0];
            para[0] = para[1];
        }
        sumy.push_back(p[b]-p[a-1]);
        pary.push_back(para);
    }
    for (int i=0; i<sumy.size(); i++) {
        cout << "[" << pary[i][0] << ", " << pary[i][1] << "]: ";
        cout << sumy[i] << endl;
    }
    return 0;
}
