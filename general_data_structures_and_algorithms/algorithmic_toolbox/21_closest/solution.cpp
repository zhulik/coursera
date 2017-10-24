#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

template <typename T> class Point {
public:
  Point(){};
  Point(T x, T y, size_t id) : m_x(x), m_y(y), m_id(id) {}
  double distance(const Point<T> &other) const {
    return sqrt(pow(other.m_x - m_x, 2) + pow((other.m_y - m_y), 2));
  }

  bool operator==(const Point<T> &other) const { return m_id == other.m_id; }

  bool operator!=(const Point<T> &other) const { return !((*this) == other); }

  T x() const { return m_x; }
  T y() const { return m_y; }

private:
  T m_x = 0;
  T m_y = 0;
  size_t m_id = -1;
};

template <typename T> double brute(const vector<Point<T>> &points) {
  double min = points[0].distance(points[1]);

  for (auto a : points) {
    for (auto b : points) {
      if (a.distance(b) < min && a != b) {
        min = a.distance(b);
      }
    }
  }

  return min;
}

template <typename T> double strip_closest(const vector<Point<T>> &strip, double d) {
  auto min = d;
  for (int i = 0; i < strip.size(); ++i)
        for (int j = i+1; j < strip.size() && (strip[j].y() - strip[i].y()) < min; ++j)
            if (strip[i].distance(strip[j]) < min)
                min = strip[i].distance(strip[j]);
  return min;
}

template <typename T> double closest(const vector<Point<T>> &points) {
  if (points.size() <= 3) {
    return brute(points);
  }

  int mid = points.size() / 2;
  auto midPoint = points[mid];
  vector<Point<T>> lp(points.begin(), points.begin() + mid);
  vector<Point<T>> rp(points.begin() + mid + 1, points.end());

  auto lc = closest(lp);
  auto rc = closest(rp);

  auto d = min(lc, rc);

  vector<Point<T>> strip;
  int j = 0;
  for (size_t i = 0; i < points.size(); i++)
    if (abs(points[i].x() - midPoint.x()) < d)
      strip.push_back(points[i]);
  std::sort(strip.begin(), strip.end(), [](const auto &f, const auto &s) { return f.y() < s.y(); });
  auto sc = strip_closest(strip, d);
  return min(d, sc);
}

int main() {
  size_t n;
  cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  vector<Point<long long>> points(n);
  for (size_t i = 0; i < n; i++) {
    points[i] = Point<long long>(x[i], y[i], i);
  }
  std::sort(points.begin(), points.end(), [](const auto &f, const auto &s) { return f.x() < s.x(); });
  cout << fixed;
  cout << setprecision(9) << closest(points) << endl;
}
