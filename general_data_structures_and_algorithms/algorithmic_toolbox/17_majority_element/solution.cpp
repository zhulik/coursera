#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
T get_majority_element(const vector<T> &a, int left, int right) {
  if (left == right) return a[left];
  int mid = left + ((right - left) >> 1);

  T lm = get_majority_element(a, left, mid);
  T rm = get_majority_element(a, mid + 1, right);
  if (lm == rm) return lm;

  return count(a.begin() + left, a.begin() + right + 1, lm) >
          count(a.begin() + left, a.begin() + right + 1, rm) ? lm : rm;
}

int main() {
  int n;
  cin >> n;
  vector<long long> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
  auto item = get_majority_element(a, 0, a.size());
  cout << (count(a.begin(), a.end(), item) > a.size() / 2) << '\n';
}
