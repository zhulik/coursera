#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class Segment {
public:
  Segment(int start, int end) : m_start(start), m_end(end) {}

  int start() const {
    return m_start;
  }

  int end() const {
    return m_end;
  }

  bool contains(int p) const {
    return p >= m_start && p <= m_end;
  }

  bool operator<(const Segment &other) const {
    return m_end < other.m_end;
  }

private:
  int m_start = 0;
  int m_end = 0;
};

vector<int> optimal_points(const vector<Segment> &segments) {
  vector<int> points;
  int prev_point = -1;
  for (auto i=0; i < segments.size(); i++) {
    if (prev_point == -1) {
      prev_point = segments[i].end();
      points.push_back(prev_point);
    } else {
      if (segments[i].contains(prev_point)){
        continue;
      } else {
        prev_point = -1;
        i--;
      }
    }
  }
  return points;
}

int main() {
  int n;
  cin >> n;
  vector<Segment> segments;
  for (size_t i = 0; i < n; ++i) {
    int start, end;
    cin >> start >> end;
    segments.push_back(Segment(start, end));
  }
  sort(segments.begin(), segments.end());
  vector<int> points = optimal_points(segments);
  cout << points.size() << endl;
  for (size_t i = 0; i < points.size(); ++i) {
    cout << points[i] << " ";
  }
}
