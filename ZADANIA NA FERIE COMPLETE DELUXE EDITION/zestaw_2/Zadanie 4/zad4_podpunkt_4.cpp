#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
int main() {
    ofstream wynik("wyniki_4.txt", ios::app);
    float wyp = 20;
    float end_power = 1;
    while (true) {
        float x = 4000;
        float w = 1000;
        float power = x/(x+w);
        float sum = x+w;
        for (int minute=1;minute <= 1500; minute++) {
            if (minute % 2 == 0) {
                w -= wyp*(1-power);
                x -= wyp*power;
                sum = x+w;
                power = x/(x+w);
            }
            if ((minute-1) % 50 == 0 && minute != 1) {
                w += 5000-sum;
                sum = x+w;
                power = x/(x+w);
            }
        }
        if (power < 0.01) {
            cout << wyp-0.01 << " " << end_power;
            float il = round((wyp-0.01)*100)/100;
            cout << endl << il;
            wynik << "4_4" << endl;
            wynik << "Maksymalna objetosc: " << il << "ml" << endl;
            return 0;
        }
        else end_power = power;
        wyp += 0.01;
    }
}
