#include <iostream>
#include <array>

using namespace std;

const int RUN = 16;


void insertion_sort(int arr[], int start, const int RUN) {
 int temp;
 int j;
 for (int i = start; i < (start+RUN); ++i) { // start is the beginning of the unsorted portion
  temp = arr[i];
  j = i - 1;
  while (arr[j] > temp && j >= start-1) {
   arr[j+1] = arr[j];
   --j;
  }
  arr[j+1] = temp;
 }
}

void merge_sort(int arr[], int start, int end) {
 if (start < end) {
  int mid = (start + end) / 2;
  merge_sort(arr, start, mid);
  merge_sort(arr, mid + 1, end);
  merge_sort
 }
}

void tim_sort(int arr[], const int RUN) {
 //insertion_sort(arr)
}

int main() {
 int arr [RUN*3];
 for (int i = 0; i < 48; ++i) {
  arr[i] = 100 - i;
  cout << arr[i] << endl;
 }
 cout << endl << endl;
 
 for (int k = 0; k < 48; k = k + RUN)
  insertion_sort(arr, k+1, RUN-1);

 for (int j = 0; j < 48; ++j)
  cout << arr[j] << endl;
 
}