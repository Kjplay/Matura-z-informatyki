#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
void selection_sort(vector <int> &arr) {
  int min_index;
  for (int i = 0; i < arr.size(); i++) {
    min_index = i; //wybieramy jakis element - pierwszy z nieposortowanych
    for (int j = i; j < arr.size(); j++) {
      if (arr[min_index] > arr[j]) {
        min_index = j; //znajdujemy najmniejszy z nieposortowanych
      }
    }
    swap(arr[i], arr[min_index]); //wsadzamy go na prawa strone posortowanych - te po lewej sa mniejsze od niego
  }
}
int main() {
  vector <int> arr;
  ifstream dane("dane.txt");
  int tmp;
  while (dane >> tmp) arr.push_back(tmp);

  cout << "Original: ";
  for (int i : arr) cout << i << " ";
  selection_sort(arr);
  cout << "\nSorted: ";
  for (int i : arr) cout << i << " ";
}
