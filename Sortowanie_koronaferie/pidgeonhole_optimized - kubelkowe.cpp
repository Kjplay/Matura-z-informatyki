#include <map>
#include <vector>
#include <iostream>
using namespace std;
void pidgeonhole_sort(vector <int> &arr) {
    map <int, int> kubelki;
    for (int i : arr) kubelki[i]++;
    arr.clear();
    for (pair <int, int> p : kubelki) {
        while(p.second-- > 0) {
            arr.push_back(p.first);
        }
    }
}
int main() {
  vector <int> arr{2, 45, 23, 12, 34, 2, 1, 3};
  cout << "Original: ";
  for (int i : arr) cout << i << " ";
  pidgeonhole_sort(arr);
  cout << "\nSorted: ";
  for (int i : arr) cout << i << " ";
}