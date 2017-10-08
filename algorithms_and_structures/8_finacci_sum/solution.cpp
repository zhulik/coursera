#include <iostream>

using namespace std;

template<typename T> int fibonacci_sum_fast(T n) {
  n = n % 60;

  if (n <= 1)
      return n;
  T previous = 0;
  T current  = 1;

  for (T i = 0; i < n - 1; ++i) {
      T tmp_previous = previous;
      previous = current;
      current = (tmp_previous + current + 1)  % 10;
  }

  return current % 10;
}

int main() {
    long long n = 0;
    cin >> n;
    cout << fibonacci_sum_fast(n) << endl;
}
