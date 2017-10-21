#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>

using namespace std;

void print_vector(const vector<int> &a) {
  for(int i=0; i<a.size(); i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

std::pair<int, int> partition3(vector<int> &a, const int l, const int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);

  x = j;
  for (int i = l; i < j; i++) {
    if (a[i] == a[j]) {
      x--;
      swap(a[i], a[x]);
    }
  }
  print_vector(a);
  cout << l <<" " << j << " " << r << endl;
  return pair<int, int>(j, j);
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  auto ms = partition3(a, l, r);

  randomized_quick_sort(a, l, ms.first - 1);
  randomized_quick_sort(a, ms.second + 1, r);
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    cout << a[i] << ' ';
  }
}
