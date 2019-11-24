/*
Ben Reilly 
Eric Gustin
Brian Steuber
Chris Fergueson 

This cpp file implements timsort on an array
Timsort uses insertion sort to initally sort 
the array, then after this uses mergesort to 
then get the final sorted array
*/

#include <iostream>
#include <fstream>
#include <chrono>
#include <assert.h>

using namespace std;

int* file_to_array(string file_name, int &length);
void print_arr(int *arr, int length);
int run_timsort_test(int *arr, int length);
void timsort(int *arr, int length);
void insertion_sort(int *arr, int length);
void merge(int *arr, int left_index, int right_index, int mid_index);
bool checkSort(int *arr, int length);

int main(int argc, char** argv) // filename that contains the array is argv[1]
{
   int *arr0;
   int len0 = 0;
   int time;
   string file0 = argv[1];
   cout << file0 << endl;
   arr0 = file_to_array(file0, len0); 
   time = run_timsort_test(arr0, len0);
   cout<<time<<" microseconds"<<endl;
   assert(checkSort(arr0, len0));
   delete [] arr0;
   return 0;
}

// function that implements timsort on an array 
// using insertion_sort and merge
void timsort(int *arr, int length)
{
   int run = 64; 
   int i;
   for(i = 0; i < length - run; i += run)
   {
      insertion_sort(arr + i, run); 
   }
   if(length % run)
      insertion_sort(arr + i, length % run);
   for(int size = run; size < length; size *= 2)
   {
      for(int left = 0; left < length; left += 2*size)
      {
         int mid = left + size - 1;
         int right;
         if((left + 2*size - 1) < (length - 1))
            right = (left + 2*size - 1);
         else
            right = (length - 1); 
         merge(arr, left, right, mid);
      }
   }
}

// function that implements insertion sort on an array
void insertion_sort(int *arr, int length)
{
   for (int i = 1; i < length; i++) 
   {  
      int sto = arr[i]; // beginning of unsorted list
      int j = i - 1; // sorted 
      while (j >= 0 && arr[j] > sto)
      {  
         arr[j + 1] = arr[j];  
         j = j - 1;  
      }  
      arr[j + 1] = sto; // increment unsorted list
    }  
}

// function that implements merge sort to an array 
void merge(int *arr, int left_index, int right_index, int mid_index)
{
   int l_len = mid_index - left_index + 1,
       r_len = right_index - mid_index; 
   int l_arr[l_len];
   int r_arr[r_len];
   for(int i = 0; i < l_len; i++)
      l_arr[i] = arr[i + left_index];
   for(int i = 0; i < r_len; i++)
      r_arr[i] = arr[i + mid_index + 1];
   int left_iter = 0,
       right_iter = 0,
       arr_iter = left_index;
   while(left_iter < l_len && right_iter < r_len) // while there are values to be read
   {
      if(l_arr[left_iter] <= r_arr[right_iter]) // case if left is <= right
      {
         arr[arr_iter] = l_arr[left_iter];
         left_iter++;
      }
      else // case if left > right
      {
         arr[arr_iter] = r_arr[right_iter];
         right_iter++;
      }
      arr_iter++; // increment
   }
   while(left_iter < l_len) // assigns left array
   {
      arr[arr_iter] = l_arr[left_iter];
      arr_iter++;
      left_iter++;
   }
   while(right_iter < r_len) // assigns right array 
   {
      arr[arr_iter] = r_arr[right_iter];
      arr_iter++;
      right_iter++;
   }
}

//function that takes in a file and returns the array 
int* file_to_array(string file_name, int &length)
{
   fstream in_file;
   in_file.open(file_name.c_str());
   int arr_len;
   int *arr_ptr;
   //File Length at top of file;
   if(in_file)
      in_file>>arr_len;
   arr_ptr = new int[arr_len];
   int i = 0;
   while(in_file)
   {
      int num;
      in_file>>num;
      arr_ptr[i] = num;
      i++;
   }
   length = arr_len;
   return arr_ptr;
}

// function that prints array
void print_arr(int *arr, int length)
{
   for(int i = 0; i < length; i++)
   {
      cout<<i<<": "<<arr[i]<<endl;
   }
   cout<<endl;
}

// function that returns true if values are in order 
bool checkSort(int *arr, int length)
{
   for(int i = 1; i < length; i++)
   {
      if(arr[i - 1] > arr[i])
      {
         return false;
      }
   }
   return true;
}

// function that runs the tests 
int run_timsort_test(int *arr, int length)
{
   using namespace std::chrono;
   high_resolution_clock::time_point start = high_resolution_clock::now();
   timsort(arr, length);
   high_resolution_clock::time_point stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
   return duration.count();
}