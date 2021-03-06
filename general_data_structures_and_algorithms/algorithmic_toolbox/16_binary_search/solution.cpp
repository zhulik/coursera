#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int binary_search(const vector<int> &a, int x, int begin, int end) {
  if (begin > end)
    return -1;

  int mid = (begin + end) / 2;
  if (a[mid] == x)
    return mid;

  if (a[mid] > x )
    return binary_search(a, x, begin, mid-1);

  if (a[mid] < x )
    return binary_search(a, x, mid+1, end);
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    cin >> a[i];
  }
  int m;
  cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    cin >> b[i];
  }
  for (auto x: b) {
    cout << binary_search(a, x, 0, a.size() -1) << ' ';
  }
}
