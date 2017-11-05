#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T> void print(const std::vector<std::vector<T>> &tries) {
  for(auto row: tries) {
    for(auto item: row) {
      cout << item << " ";
    }
    cout << endl;
  }
}

template<typename T>
T optimal_weight(T W, const vector<T> &items) {
  T n = items.size();
  std::vector<std::vector<T>>tries(W + 1, std::vector<T>(n + 1, 0));


  for(T i = 1; i <= n; i++ ) {
    for(T w = 1; w <= W; w++) {
      tries[w][i] = tries[w][i - 1];
      if (items[i-1] <= w) {
        T val = tries[w - items[i-1]][i-1] + items[i-1];
        if (tries[w][i] < val)
          tries[w][i] = val;
      }
    }
  }
  return tries[W][n];
}

int main() {
  int n, W;
  cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    cin >> w[i];
  }
  cout << optimal_weight(W, w) << endl;
}
