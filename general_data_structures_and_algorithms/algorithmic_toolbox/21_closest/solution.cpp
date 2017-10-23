#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

template<typename T>
class Point {
public:
  Point(){};
  Point(T x, T y, size_t id): m_x(x), m_y(y), m_id(id) {}
  double distance(const Point<T> &other) const {
    return sqrt(pow(other.m_x - m_x, 2) + pow((other.m_y - m_y), 2));
  }

  bool operator==(const Point<T> &other) const {
    return m_id == other.m_id;
  }

  bool operator!=(const Point<T> &other) const {
    return !((*this) == other);
  }

  bool operator<(const Point<T> &other) const {
    return m_x < other.m_x;
  }

  T x() const { return m_x; }
  T y() const { return m_y; }

private:
  T m_x = 0;
  T m_y = 0;
  size_t m_id = -1;
};

template<typename T, typename M>
double median(vector<Point<T>> points, M m)
{
  double median;
  size_t size = points.size();

  if (size  % 2 == 0) {
      median = (double)((points[size / 2 - 1].*m)() + (points[size / 2].*m)()) / 2;
  }
  else {
      median = points[size / 2].x();
  }

  return median;
}

double minimal_distance(const vector<Point<long long>> &points) {
  double min = points[0].distance(points[1]);

  for(auto a: points){
    for(auto b: points){
      if (a.distance(b) < min && a != b) {
        min = a.distance(b);
      }
    }
  }

  return min;
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
  std::sort(points.begin(), points.end());
  cout << median(points, &Point<long long>::x) << endl;
  cout << fixed;
  cout << setprecision(9) << minimal_distance(points) << endl;
}
