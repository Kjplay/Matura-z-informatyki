#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
void quicksort(vector <int> &arr,int left = 0,int right = -1) {
  if (right == -1) right = arr.size()-1;
  int Partition = left;
  int pivot = right; //wybieramy wartosc na ktora dzielmy
  int pivotval = arr[pivot];
  if (left < right) { //jezeli jest co dzielic
    for (int i = left; i < right; i++) {
      if (arr[i] < pivotval) { //przesuwaj
        swap(arr[i], arr[Partition]);
        Partition++; //na lewo od przegrody jest ok
      }
    }
    swap(arr[Partition], arr[pivot]); //zamien wartosc z przegroda
    quicksort(arr, left, Partition - 1);
    quicksort(arr, Partition + 1, right);
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
  quicksort(tab);
  for (int i : tab) cout << i << " ";
}
