#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
void insertion_sort(vector <int> &arr) {
  int current, j;
  for (int i=1; i < arr.size(); i++) {
    current = arr[i]; //element do wsadzenia
    j = i - 1;
    //przygotowujemy miejsce
    while(j >= 0 && arr[j] > current) { //przesun wszystkie wieksze od arr j bo powinny byc na prawo od niego posortowane o 1 w gore
      arr[j+1] = arr[j];
      j--;
    }
    arr[j+1] = current; //wsadzamy na miejsce
  }
}
int main() {
  vector <int> arr;
  ifstream dane("dane.txt");
  int tmp;
  while (dane >> tmp) arr.push_back(tmp);
  
  cout << "Original: ";
  for (int i : arr) cout << i << " ";
  insertion_sort(arr);
  cout << "\nSorted: ";
  for (int i : arr) cout << i << " ";
}