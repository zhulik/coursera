#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef vector<int> Array;

void print_array(const Array &a) {
  for (auto n: a) {
    cout <<  n << " ";
  }
  cout << endl;
}

int merge(int arr[], int temp[], int left, int mid, int right) {
  int inv_count = 0;

  int i = left;
  int j = mid;
  int k = left;
  while ((i <= mid - 1) && (j <= right))
  {
  	if (arr[i] <= arr[j])
  	{
  	temp[k++] = arr[i++];
  	}
  	else
  	{
  	temp[k++] = arr[j++];

  	inv_count = inv_count + (mid - i);
  	}
  }

  while (i <= mid - 1)
  	temp[k++] = arr[i++];

  while (j <= right)
  	temp[k++] = arr[j++];

  for (i=left; i <= right; i++)
  	arr[i] = temp[i];

  return inv_count;
}

int mergeSort(int arr[], int temp[], int left, int right)
{
  int mid, inv_count = 0;
  if (right > left)
  {
  	mid = (right + left) / 2;

  	inv_count = mergeSort(arr, temp, left, mid);
  	inv_count += mergeSort(arr, temp, mid+1, right);

  	inv_count += merge(arr, temp, left, mid+1, right);
  }
  return inv_count;
}

int mergeSort(int arr[], int array_size)
{
	int *temp = (int *)malloc(sizeof(int)*array_size);
	return mergeSort(arr, temp, 0, array_size - 1);
}

void stressTest() {
  int arr1[] = {1, 20, 6, 4, 5};
  assert(mergeSort(arr1, 5) == 5);
  int arr2[] = {9, 9, 3, 3, 3, 3, 3, 3, 1, 1 };
  assert(mergeSort(arr2, 10) == 28);

  int arr3[] = {2, 3, 9, 2, 9 };
  assert(mergeSort(arr3, 5) == 2);
}


int main() {
  stressTest();
  // int n;
  // cin >> n;
  // Array a(n);
  // for (size_t i = 0; i < a.size(); i++) {
  //   cin >> a[i];
  // }
  // print_array(a);
  // cout << mergeSort(&a[0], a.size()) << endl;
  // print_array(a);
}
