#include <iostream>
#include <cassert>

using namespace std;

template<typename T> T get_fibonacci_partial_sum_naive(T from, T to) {
    if (to <= 1)
        return to;

    T previous = 0;
    T current  = 1;

    for (T i = 0; i < from - 1; ++i) {
        T tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    T sum = current % 10;

    for (T i = 0; i < to - from; ++i) {
        T tmp_previous = previous;
        previous = current % 10;
        current = tmp_previous + current;
        sum = (sum + current) % 10;
    }

    return sum;
}

template<typename T> int fibonacci_sum_fast(T n) {
  n = n % 60;

  if (n <= 1)
      return n;

  T previous = 0;
  T current  = 1;

  for (T i = 0; i < n - 1; ++i) {
      T tmp_previous = previous;
      previous = current % 10;
      current = (tmp_previous + current + 1);
  }

  return current % 10;
}

template<typename T> T get_fibonacci_partial_sum_fast(T from, T to) {
  auto res =  fibonacci_sum_fast(to) - fibonacci_sum_fast(from - 1);
  if (res < 0) {
    res = 10+res;
  }
  return res;
}

void test_fast() {
  for(long long from = 10; from <= 200; from++) {
    for(long long to = from + 1; to <= 200; to++) {
      if (get_fibonacci_partial_sum_fast(from, to) != get_fibonacci_partial_sum_naive(from, to)) {
        cout << from << " " << to << " " << get_fibonacci_partial_sum_fast(from, to) << " " << get_fibonacci_partial_sum_naive(from, to)<< endl;
      }
    }
  }
}

int main() {
  // test_fast();
    long long from, to;
    cin >> from >> to;
    cout << get_fibonacci_partial_sum_fast(from, to) << endl;
    // cout << get_fibonacci_partial_sum_naive(from, to) << endl;
}
