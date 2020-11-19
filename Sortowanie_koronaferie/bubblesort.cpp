#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
void bubble_sort(vector <int> &arr) {
  int n = arr.size();
  bool p = true;
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < n-i; j++) {
      p = true;
      if (arr[j-1]>arr[j]) {
        swap(arr[j-1], arr[j]);
        p = false;
      }
    }
    if (p) break; //jezeli nie bylo przestawien jest dobrze
  }
}
int main() {
  vector <int> tab;
  ifstream dane("dane.txt");
  int tmp;
  while (dane >> tmp) tab.push_back(tmp);
  
  cout << "Original: ";
  for (int i : tab) cout << i << " ";
  cout << "\nSorted: ";
  bubble_sort(tab);
  for (int i : tab) cout << i << " ";
}
