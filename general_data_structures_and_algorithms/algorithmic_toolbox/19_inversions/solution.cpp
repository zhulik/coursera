#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template<typename T>
T merge(vector<T> &arr, vector<T> &temp, size_t left, size_t mid, size_t right) {
  T inv_count = 0;

  T i = left;
  T j = mid;
  T k = left;

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

template<typename T>
T mergeSort(vector<T> &arr, vector<T> &temp, size_t left, size_t right) {
  T mid, inv_count = 0;
  if (right > left) {
  	mid = (right + left) / 2;

  	inv_count = mergeSort(arr, temp, left, mid);
  	inv_count += mergeSort(arr, temp, mid+1, right);

  	inv_count += merge(arr, temp, left, mid+1, right);
  }
  return inv_count;
}

template<typename T>
T mergeSort(vector<T> &arr) {
	vector<T> temp(arr.size());
	return mergeSort(arr, temp, 0, arr.size() - 1);
}

void stressTest() {
  vector<long long> arr2 = {9, 9, 3, 3, 3, 3, 3, 3, 1, 1 };
  assert(mergeSort(arr2) == 28);

  vector<long long> arr3 = {2, 3, 9, 2, 9 };
  assert(mergeSort(arr3) == 2);
}


int main() {
  int n;
  cin >> n;
  vector<long long> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    cin >> a[i];
  }
  cout << mergeSort(a) << endl;
}
