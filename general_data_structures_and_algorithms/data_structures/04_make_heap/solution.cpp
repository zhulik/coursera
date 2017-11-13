#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>

using namespace ::std;

class HeapBuilder {

public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }

private:
  vector<int> m_data;
  vector<pair<int, int>> m_swaps;

  void WriteResponse() const {
    cout << m_swaps.size() << endl;
    for (int i = 0; i < m_swaps.size(); ++i) {
      cout << m_swaps[i].first << " " << m_swaps[i].second << endl;
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    m_data.resize(n);
    for (int i = 0; i < n; ++i) {
      cin >> m_data[i];
    }
  }

  void SiftDown(int i) {
    int max = i;
    int l = i * 2 + 1;
    if (l < m_data.size() && m_data[l] < m_data[max]) {
      max = l;
    }
    int r = i * 2 + 2;
    if (r < m_data.size() && m_data[r] < m_data[max]) {
      max = r;
    }
    if (max != i) {
      swap(m_data[i], m_data[max]);
      m_swaps.push_back(make_pair(i, max));
      SiftDown(max);
    }
  }

  void GenerateSwaps() {
    m_swaps.clear();
    for (int i = ceil((float)m_data.size() / 2); i >= 0; i--) {
      SiftDown(i);
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
