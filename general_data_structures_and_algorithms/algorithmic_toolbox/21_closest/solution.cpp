#include <iostream>
#include <iomanip>
#include <vector>
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

private:
  T m_x = 0;
  T m_y = 0;
  size_t m_id = -1;
};

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
  cout << fixed;
  cout << setprecision(9) << minimal_distance(points) << endl;
}
