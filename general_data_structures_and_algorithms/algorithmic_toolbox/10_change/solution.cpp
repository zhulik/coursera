#include <iostream>
#include <vector>

using namespace std;

const vector<int> coins{10, 5, 1};

int get_change(int m) {
  int n = 0;
  for(auto c: coins) {
    while (m >= c) {
      m -= c;
      n++;
    }
  }
  return n;
}

int main() {
  int m;
  cin >> m;
  cout << get_change(m) << endl;
}
