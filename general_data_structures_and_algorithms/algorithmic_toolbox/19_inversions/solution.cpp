#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> Array;

int merge(Array &arr, int l, int m, int r)
{
    int count = 0;
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        count++;
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        count++;
        j++;
        k++;
    }
    return count;
}

int mergeSort(Array &arr, int l, int r, int count = 0)
{
    if (l < r)
    {
        int m = (l + r) / 2;

        mergeSort(arr, l, m, count);
        mergeSort(arr, m + 1, r, count);

        count += merge(arr, l, m, r);
    }
    return count;
}

void print_array(const Array &a) {
  for (auto n: a) {
    cout <<  n << " ";
  }
  cout << endl;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    cin >> a[i];
  }
  print_array(a);
  cout << mergeSort(a, 0, a.size()-1) << endl;
  print_array(a);
}
