#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
void merge_sort(vector <int> &arr) {
    if (arr.size() > 1) {
        //splitting
        int mid = arr.size()/2;
        vector<int> L(arr.begin(), arr.end()-mid);
        vector<int> R(arr.begin()+mid, arr.end());
        merge_sort(L);
        merge_sort(R);
        //merging
        int i = 0, j = 0, k = 0;
        while (i < L.size() && j < R.size()) {
            if (L[i] < R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            } 
            k++;
        }
        //Musimy dolozyc pozostale elementy i < l size , j < r size - ktores wywali pierwsze, wiec elementy zostana
        while (i < L.size()) {
            arr[k] = L[i];
            k++; i++;
        }
        while(j < R.size()) {
            arr[k] = R[j];
            k++; j++;
        }
    }
}
int main() {
  vector <int> arr;
  ifstream dane("dane.txt");
  int tmp;
  while (dane >> tmp) arr.push_back(tmp);
  
  cout << "Original: ";
  for (int i : arr) cout << i << " ";
  merge_sort(arr);
  cout << "\nSorted: ";
  for (int i : arr) cout << i << " ";
}