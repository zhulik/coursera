#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
T lcs3(const vector<T> X, const vector<T> Y, const vector<T> Z) {
  int m = X.size();
  int n = Y.size();
  int o = Z.size();
  vector<vector<vector<T>>> L(m + 1,
                              vector<vector<T>>(n + 1, vector<T>(o + 1, 0)));

  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      for (int k = 0; k <= o; k++) {
        if (i == 0 || j == 0 || k == 0)
          L[i][j][k] = 0;
        else if (X[i - 1] == Y[j - 1] && X[i - 1] == Z[k - 1])
          L[i][j][k] = L[i - 1][j - 1][k - 1] + 1;
        else
          L[i][j][k] = max({L[i - 1][j][k], L[i][j - 1][k], L[i][j][k - 1]});
      }
    }
  }
  return L[m][n][o];
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
