#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool is_majority(const vector<int> &a, int left, int right, int x) {
  int c = 0;
  for(int i = 0; i < a.size(); i++) {
    if (a[i] == x)
      c++;
  }
  return c > a.size() / 2;
}

int get_majority_element(const vector<int> &a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];

  int mid = (left + right) / 2;

  int lm = get_majority_element(a, left, mid);
  if (is_majority(a, left, mid, lm))
    return lm;

  int rm = get_majority_element(a, mid, right);
  if (is_majority(a, mid, right, rm))
    return rm;


  return -1;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    cin >> a[i];
  }
  cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
