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

int* merge_sort(int arr[], int start, const int RUN) {
 int sub1_index = start;
 int sub2_index = start+RUN;
 int temp [2*RUN];
 for (int i = start; i < start + RUN; ++i) {
  if (arr[sub1_index] <= arr[sub2_index]) {
   temp[i-start] = arr[sub1_index];
   ++sub1_index;
  }
  else { // sub2 value > sub1 value
   temp[i-start] = arr[sub2_index];
   ++sub2_index;
  }
 }
 return temp;
}

void tim_sort(int arr[]) {
 // create the array
 for (int i = 0; i < 48; ++i) {
  arr[i] = 100 - i;
  cout << arr[i] << endl;
 }
 cout << endl << endl;
 
 // create sorted subarrays within arr
 for (int k = 0; k < 48; k = k + RUN)
  insertion_sort(arr, k+1, RUN-1);

 // print results
 for (int j = 0; j < 48; ++j)
  cout << arr[j] << endl;

 for (int m = 0; m < 2; ++m)
  int temp [2*RUN] = merge_sort(arr, , RUN);

}

int main() {
 int arr [RUN*3];
 tim_sort(arr);
}