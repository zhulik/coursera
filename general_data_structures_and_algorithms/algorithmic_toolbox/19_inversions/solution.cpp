#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef vector<int> Array;

int merge(Array &arr, Array &temp, int left, int mid, int right) {
  int inv_count = 0;

  int i = left;
  int j = mid;
  int k = left;

  while ((i <= mid - 1) && (j <= right)) {
  	if (arr[i] <= arr[j])	{
  	temp[k++] = arr[i++];
  	}	else {
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

int mergeSort(Array &arr, Array &temp, int left, int right) {
  int mid, inv_count = 0;
  if (right > left) {
  	mid = (right + left) / 2;

  	inv_count = mergeSort(arr, temp, left, mid);
  	inv_count += mergeSort(arr, temp, mid+1, right);

  	inv_count += merge(arr, temp, left, mid+1, right);
  }
  return inv_count;
}

int mergeSort(Array &arr) {
	Array temp(arr.size());
	return mergeSort(arr, temp, 0, arr.size() - 1);
}

void stressTest() {
  Array arr2 = {9, 9, 3, 3, 3, 3, 3, 3, 1, 1 };
  assert(mergeSort(arr2) == 28);

  Array arr3 = {2, 3, 9, 2, 9 };
  assert(mergeSort(arr3) == 2);
}


int main() {
  int n;
  cin >> n;
  Array a(n);
  for (size_t i = 0; i < a.size(); i++) {
    cin >> a[i];
  }
  cout << mergeSort(a) << endl;
}
