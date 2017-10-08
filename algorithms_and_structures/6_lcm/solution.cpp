#include <iostream>

template<typename T> T gcd_fast(T a, T b) {
  while ( a != 0 ) {
    T tmp = a;
    a = b % a;
    b = tmp;
  }
  return b;
}

template<typename T> T lcm_fast(T a, T b) {
  return a * b / gcd_fast(a, b);
}

int main() {
  long long a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
