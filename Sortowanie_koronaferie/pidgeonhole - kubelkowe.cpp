#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void pidgeonhole_sort(vector <int> &arr) {
  int mi = *min_element(arr.begin(), arr.end()),
  range = *max_element(arr.begin(), arr.end()) - mi + 1;
  int holes[range] = {0}; //dziala bo range jest z pointera
  for (int i = 0; i < arr.size(); i++) {
    holes[arr[i] - mi]++;
  }
  int x = 0;
  for (int i = 0; i < range; i++) {
    while (holes[i] > 0) {
      holes[i]--;
      arr[x] = i + mi;
      x++;
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
