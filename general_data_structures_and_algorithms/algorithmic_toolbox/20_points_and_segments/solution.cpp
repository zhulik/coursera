#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

template<typename T>
class Range {
public:
  Range() {};
  Range(T start, T end) : m_start(start), m_end(end) {}

  T start() const { return m_start; }
  T end() const { return m_end; }

private:
  T m_start = 0;
  T m_end = 0;
};

template<typename T>
class MarkedPoint {
public:
  enum Position {
    Left = 0,
    Point = 1,
    Right = 2
  };

  MarkedPoint() {}
  MarkedPoint(T point, Position position, int point_pos = -1): m_point(point), m_position(position), m_point_pos(point_pos) {}
  bool operator<(const MarkedPoint<T> &other) const { return tie(m_point, m_position) < tie(other.m_point, other.m_position); }

  T point() const { return m_point; };
  Position position() const { return m_position; }
  int index() const { return m_point_pos; }

private:
  T m_point = 0;
  Position m_position = Left;
  int m_point_pos = -1;
};

template<typename T>
vector<MarkedPoint<T>> markedPoints(const vector<Range<T>> &ranges, const vector<T> &points) {
  vector<MarkedPoint<T>> res(ranges.size() * 2 + points.size());
  int pos = 0;
  for(auto r: ranges) {
    res[pos++] = MarkedPoint<T>(r.start(), MarkedPoint<T>::Left);
    res[pos++] = MarkedPoint<T>(r.end(), MarkedPoint<T>::Right);
  }
  for(auto i = 0; i < points.size(); i++) {
    res[pos++] = MarkedPoint<T>(points[i], MarkedPoint<T>::Point, i);
  }

  sort(res.begin(), res.end());

  return res;
}


template<typename T>
vector<T> fast_count_segments(const vector<Range<T>> &ranges, const vector<T> &points) {
  vector<T> cnt(points.size(), 0);
  int c = 0;

  auto pps = markedPoints(ranges, points);
  for(auto p: pps) {
    if (p.position() == MarkedPoint<T>::Left) {
      c++;
    }
    if (p.position() == MarkedPoint<T>::Right) {
      c--;
    }
    if (p.position() == MarkedPoint<T>::Point) {
      cnt[p.index()] = c;
    }
  }

  return cnt;
}

template<typename T>
vector<T> naive_count_segments(const vector<Range<T>> &ranges, const vector<T> &points) {
  vector<T> cnt(points.size());
  for (int i = 0; i < points.size(); i++) {
    for (auto r: ranges) {
      cnt[i] += r == points[i];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<long long> starts(n), ends(n);
  for (int i = 0; i < starts.size(); i++) {
    cin >> starts[i] >> ends[i];
  }

  vector<long long> points(m);
  for (int i = 0; i < points.size(); i++) {
    cin >> points[i];
  }

  vector<Range<long long>> ranges(n);
  for (int i = 0; i < n; i++) {
    ranges[i] = Range<long long>(starts[i], ends[i]);
  }

  auto cnt = fast_count_segments(ranges, points);
  for (auto c: cnt) {
    cout << c << " ";
  }
}
