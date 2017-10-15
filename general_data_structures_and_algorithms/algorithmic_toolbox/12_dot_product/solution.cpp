#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<typename T> T max_dot_product(vector<T> a, vector<T> b) {
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  long long result = 0;
  for (size_t i = 0; i < a.size(); i++) {
    result += ((long long) a[i]) * b[i];
  }
  return result;
}

int main() {
  size_t n;
  cin >> n;
  vector<long long> a(n), b(n);
  for (auto i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (auto i = 0; i < n; i++) {
    cin >> b[i];
  }
  cout << max_dot_product(a, b) << endl;
}
