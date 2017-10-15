#include <iostream>

using namespace std;

template<typename T> T gcd_fast(T a, T b) {
  while ( a != 0 ) {
    T tmp = a;
    a = b % a;
    b = tmp;
  }
  return b;
}

int main() {
  long long a, b;
  cin >> a >> b;
  cout << gcd_fast(a, b) << std::endl;
  return 0;
}
