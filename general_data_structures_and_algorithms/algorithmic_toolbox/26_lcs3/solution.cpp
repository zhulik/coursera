#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T> T lcs(const vector<T> X, const vector<T> Y) {
  T m = X.size();
  T n = Y.size();
  vector<vector<T>> L(m + 1, vector<T>(n + 1, 0));

  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == 0 || j == 0)
        L[i][j] = 0;

      else if (X[i - 1] == Y[j - 1])
        L[i][j] = L[i - 1][j - 1] + 1;

      else
        L[i][j] = max(L[i - 1][j], L[i][j - 1]);
    }
  }

  return L[m][n];
}

template <typename T> T lcs3(vector<T> &a, vector<T> &b, vector<T> &c) {
  return min({lcs(a, b), lcs(b, c), lcs(a, c)});
}

int main() {
  size_t an;
  cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    cin >> a[i];
  }
  size_t bn;
  cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    cin >> b[i];
  }
  size_t cn;
  cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    cin >> c[i];
  }
  cout << lcs3(a, b, c) << endl;
}
